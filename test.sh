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
CHEMIN_CSV=$1
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

# Variable pour stocker le fichier de sortie
FICHIER_SORTIE="resultat_intermediaire.txt"

# Traitement selon les options
echo "Traitement des données en cours..."
if [[ "$TYPE_STATION" == "hva" && "$TYPE_CONSOMMATEUR" == "comp" ]]; then
  awk -F";" -v centrale="$CENTRALE_ID" '
    NR > 1 { 
        if (centrale == "" || $1 == centrale) {
            if ($3 != "-" && $4 == "-" && $6 == "-") {
                gsub("-", "0", $3);
                gsub("-", "0", $7);
                gsub("-", "0", $8);
                print $3, $7, $8;
            }
        }
    }' "$CHEMIN_CSV" > "$FICHIER_SORTIE"
elif [[ "$TYPE_STATION" == "hvb" && "$TYPE_CONSOMMATEUR" == "comp" ]]; then
  awk -F";" -v centrale="$CENTRALE_ID" '
    NR > 1 {
        if (centrale == "" || $1 == centrale) {
            if ($2 != "-" && $3 == "-" && $4 == "-" && $6 == "-") {
                gsub("-", "0", $2);
                gsub("-", "0", $7);
                gsub("-", "0", $8);
                print $2, $7, $8;
            }
        }
    }' "$CHEMIN_CSV" > "$FICHIER_SORTIE"
elif [[ "$TYPE_STATION" == "lv" && "$TYPE_CONSOMMATEUR" == "all" ]]; then
  awk -F";" -v centrale="$CENTRALE_ID" '
    NR > 1 {
        if (centrale == "" || $1 == centrale) {
            gsub("-", "0", $0);
            if ($4 != "0") {
                print $4, $7, $8;
            }
        }
    }' "$CHEMIN_CSV" > "$FICHIER_SORTIE"
fi

# Vérification si un fichier de sortie a été créé
if [[ ! -f "$FICHIER_SORTIE" ]]; then
  echo "Erreur : Aucun fichier de sortie généré."
  exit 1
fi

# Compilation
echo "Compilation du programme C..."
make clean
make
if [[ $? -ne 0 ]]; then
  echo "Erreur : Échec de la compilation du programme C."
  exit 1
fi

# Lancer le programme C avec le fichier de sortie
echo "Lancement du programme C avec le fichier de sortie : $FICHIER_SORTIE"
./exec "$FICHIER_SORTIE"
if [[ $? -ne 0 ]]; then
  echo "Erreur : Le programme C a rencontré un problème lors de l'exécution."
  exit 1
fi

echo "Traitement terminé."
