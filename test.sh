#!/bin/bash

# Fonction pour afficher l'aide
afficher_aide() {
  echo " "
  echo "Usage: $0 <chemin_csv> <type_station> <type_consommateur> [identifiant_centrale]"
  echo
  echo "Options :"
  echo "  <chemin_csv>         Chemin du fichier CSV contenant les données."
  echo "  <type_station>       Type de station à traiter (hvb, hva, lv)."
  echo "  <type_consommateur>  Type de consommateur (comp, indiv, all)."
  echo "  [identifiant_centrale] (Optionnel) Identifiant de la centrale spécifique à analyser."
  echo
  echo "Exemple :"
  echo "  $0 ./data.csv hva comp 2"
  exit 0
}
 
if [ -d "input" ]; then
    echo "existe déjà"
else
    mkdir input
    echo "Le dossier 'input' a été créé."
fi
	
 
# Vérifier si l'option -h est présente
for arg in "$@"; do
  if [[ "$arg" == "-h" ]]; then
    afficher_aide
  fi
done

# Validation des paramètres obligatoires
if [[ $# -lt 3 ]]; then
  echo "Erreur : Nombre de paramètres insuffisant."
  echo "Utilisez l'option -h pour afficher l'aide."
  exit 1
fi

# Paramètres
CHEMIN_CSV=input/$1
TYPE_STATION=$2
TYPE_CONSOMMATEUR=$3
CENTRALE_ID=${4:-""}

# Validation des paramètres
if [[ "$TYPE_STATION" != "hvb" && "$TYPE_STATION" != "hva" && "$TYPE_STATION" != "lv" ]]; then
  echo "Erreur : Type de station invalide. Valeurs possibles : hvb, hva, lv."
  exit 1
fi

if [[ "$TYPE_CONSOMMATEUR" != "comp" && "$TYPE_CONSOMMATEUR" != "indiv" && "$TYPE_CONSOMMATEUR" != "all" ]]; then
  echo "Erreur : Type de consommateur invalide. Valeurs possibles : comp, indiv, all."
  exit 1
fi

if [[ ! -f "$CHEMIN_CSV" ]]; then
  echo "Erreur : Fichier CSV introuvable : $CHEMIN_CSV"
  exit 1
fi

# Gestion du dossier tmp
TMP_DIR="tmp"

if [[ -d "$TMP_DIR" ]]; then
  echo "Le dossier '$TMP_DIR' existe déjà."
  # Vérifier s'il y a des fichiers à l'intérieur
  if [[ "$(ls -A $TMP_DIR)" ]]; then
    echo "Suppression des fichiers à l'intérieur de '$TMP_DIR'..."
    rm -f "$TMP_DIR"/*
    if [[ $? -ne 0 ]]; then
      echo "Erreur : Impossible de supprimer les fichiers dans '$TMP_DIR'."
      exit 1
    fi
    echo "Les fichiers ont été supprimés."
  else
    echo "Le dossier '$TMP_DIR' est déjà vide."
  fi
else
  echo "Création du dossier '$TMP_DIR'..."
  mkdir "$TMP_DIR"
  if [[ $? -ne 0 ]]; then
    echo "Erreur : Impossible de créer le dossier '$TMP_DIR'."
    exit 1
  fi
  echo "Le dossier '$TMP_DIR' a été créé."
fi

# Variable pour stocker le fichier de sortie
avant_c="$TMP_DIR/resultat_intermediaire.txt"

# Traitement selon les options
echo "Traitement des données en cours..."
awk -F";" -v centrale="$CENTRALE_ID" -v type_station="$TYPE_STATION" -v type_consommateur="$TYPE_CONSOMMATEUR" '
NR > 1 {
    if (centrale == "" || $1 == centrale) {
        gsub("-", "0", $0);
        if (type_station == "hva" && type_consommateur == "comp" && $3 != "0" && $4 == "0" && $6 == "0") {
            print $3, $7, $8;
        } else if (type_station == "hvb" && type_consommateur == "comp" && $2 != "0" && $3 == "0" && $4 == "0" && $6 == "0") {
            print $2, $7, $8;
        } else if (type_station == "lv" && type_consommateur == "all" && $4 != "0") {
            print $4, $7, $8;
        } else if (type_station == "lv" && type_consommateur == "indiv" && $4 != "0" && $5 == "0") {
            print $4, $7, $8;
        } else if (type_station == "lv" && type_consommateur == "comp" && $4 != "0" && $6 == "0") {
            print $4, $7, $8;
        }
    }
}' "$CHEMIN_CSV" > "$avant_c"

# Vérification si un fichier de sortie a été créé
if [[ ! -s "$avant_c" ]]; then
  echo "Erreur : Aucun fichier de sortie généré ou fichier vide."
  exit 1
fi

# Compilation
echo "Compilation du programme C..."
make clean && make
if [[ $? -ne 0 ]]; then
  echo "Erreur : Échec de la compilation du programme C."
  exit 1
fi

# Lancer le programme C avec le fichier de sortie
echo "Lancement du programme C avec le fichier de sortie : $avant_c"
./exec "$avant_c"
if [[ $? -ne 0 ]]; then
  echo "Erreur : Le programme C a rencontré un problème lors de l'exécution."
  exit 1
fi

# Création du répertoire de sortie
mkdir -p output

# Tri et enregistrement des résultats finaux
sort -t ':'  -k2,2n resultat.txt > output/"${TYPE_STATION}_${TYPE_CONSOMMATEUR}.csv"
echo "Traitement terminé. Les résultats sont disponibles dans output/${TYPE_STATION}_${TYPE_CONSOMMATEUR}.csv"

  


