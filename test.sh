#!/bin/bash

# Fonction pour afficher l'aide
afficher_aide() {
  echo " "
  echo "Usage: $0 <nom_fichier> <type_station> <type_consommateur> [identifiant_centrale]"
  echo
  echo "Options :"
  echo "  <nom_fichier>        Nom du fichier CSV situé dans le dossier 'input'."
  echo "  <type_station>       Type de station à traiter (hvb, hva, lv)."
  echo "  <type_consommateur>  Type de consommateur (comp, indiv, all)."
  echo "  [identifiant_centrale] (Optionnel) Identifiant de la centrale spécifique à analyser."
  echo
  echo "Exemple :"
  echo "  $0 data.csv hva comp 2"
  exit 0
}

# Création du dossier "input" s'il n'existe pas
if [[ ! -d "input" ]]; then
  mkdir input
  echo "Le dossier 'input' a été créé."
else
  echo "Le dossier 'input' existe déjà."
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
NOM_FICHIER="$1"
CHEMIN_CSV="input/$NOM_FICHIER"
TYPE_STATION="$2"
TYPE_CONSOMMATEUR="$3"
CENTRALE_ID=${4:-""}

# Vérification de l'existence du fichier CSV dans "input"
if [[ ! -f "$CHEMIN_CSV" ]]; then
  echo "Erreur : Le fichier $NOM_FICHIER n'existe pas dans le dossier 'input'."
  exit 1
fi

# Suppression ou conservation du contenu du dossier tmp
TMP_DIR="tmp"
RESULT_DIR="resultat"
OUTPUT_DIR="output"

if [[ -d "$TMP_DIR" ]]; then
  echo -n "Voulez-vous effacer le contenu du dossier 'tmp' ? (o/n) : "
  read reponse
  if [[ "$reponse" == "o" || "$reponse" == "O" ]]; then
    rm -rf "$TMP_DIR"/*
    echo "Le contenu du dossier 'tmp' a été supprimé."
  else
    echo "Le contenu du dossier 'tmp' a été conservé."
  fi
else
  mkdir "$TMP_DIR"
  echo "Le dossier 'tmp' a été créé."
fi

# Gestion des dossiers output et resultat
if [[ -d "$OUTPUT_DIR" && $(ls -A "$OUTPUT_DIR") ]]; then
  mkdir -p "$RESULT_DIR"
  mv "$OUTPUT_DIR"/* "$RESULT_DIR"/
  echo "Les fichiers existants du dossier 'output' ont été déplacés vers '$RESULT_DIR'."
else
  mkdir -p "$OUTPUT_DIR"
  echo "Le dossier 'output' est prêt pour les nouveaux fichiers."
fi

# Début du chronomètre
debut=$(date +%s)

# Variable pour stocker le fichier de sortie
SORTIE_INTERMEDIAIRE="$TMP_DIR/resultat_intermediaire.txt"

# Traitement des données avec awk
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
}' "$CHEMIN_CSV" > "$SORTIE_INTERMEDIAIRE"

if [[ ! -s "$SORTIE_INTERMEDIAIRE" ]]; then
  echo "Erreur : Aucun fichier de sortie généré ou fichier vide."
  debut=0
  exit 1
fi

# Compilation du programme C
make clean && make
if [[ $? -ne 0 ]]; then
  echo "Erreur : Échec de la compilation du programme C."
  debut=0
  exit 1
fi

# Exécution du programme C
./exec "$SORTIE_INTERMEDIAIRE"
if [[ $? -ne 0 ]]; then
  echo "Erreur : Le programme C a rencontré un problème lors de l'exécution."
  debut=0
  exit 1
fi

# Déplacement de resultat.txt vers tmp
if [[ -f "resultat.txt" ]]; then
  mv resultat.txt "$TMP_DIR/"
  echo "Le fichier resultat.txt a été déplacé vers le dossier 'tmp'."
fi

# Calcul du temps écoulé
fin=$(date +%s)
temps_execution=$((fin - debut))

# Enregistrement des résultats finaux dans output
sort -t ':' -k2,2n "$TMP_DIR/resultat.txt" > "$OUTPUT_DIR/${TYPE_STATION}_${TYPE_CONSOMMATEUR}.csv"

if [[ $debut -ne 0 ]]; then
  echo "Traitement terminé en $temps_execution secondes. Les résultats sont disponibles dans '$OUTPUT_DIR/${TYPE_STATION}_${TYPE_CONSOMMATEUR}.csv'"
else
  echo "Le temps d'exécution a été réinitialisé à 0 à cause d'une erreur."
fi

