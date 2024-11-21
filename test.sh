#!/bin/bash

# Fonction pour afficher l'aide
afficher_aide() {
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

# Vérifier si l'option -h est présente parmi les arguments
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

CHEMIN_CSV=$1
TYPE_STATION=$2
TYPE_CONSOMMATEUR=$3
CENTRALE_ID=${4:-""}

# Valider le type de station
if [[ "$TYPE_STATION" != "hvb" && "$TYPE_STATION" != "hva" && "$TYPE_STATION" != "lv" ]]; then
  echo "Erreur : Type de station invalide. Valeurs possibles : hvb, hva, lv."
  echo "Utilisez l'option -h pour afficher l'aide."
  exit 1
fi

# Valider le type de consommateur
if [[ "$TYPE_CONSOMMATEUR" != "comp" && "$TYPE_CONSOMMATEUR" != "indiv" && "$TYPE_CONSOMMATEUR" != "all" ]]; then
  echo "Erreur : Type de consommateur invalide. Valeurs possibles : comp, indiv, all."
  echo "Utilisez l'option -h pour afficher l'aide."
  exit 1
fi

# Vérification et préparation des répertoires requis
for dir in tmp graphs; do
  if [[ ! -d $dir ]]; then
    mkdir -p $dir && echo "Le dossier '$dir' a été créé."
  else
    rm -rf $dir/* && echo "Le contenu du dossier '$dir' a été nettoyé."
  fi
done

# Vérification de l'existence du fichier CSV
if [[ ! -f "$CHEMIN_CSV" ]]; then
  echo "Erreur : Fichier CSV introuvable : $CHEMIN_CSV"
  echo "Utilisez l'option -h pour afficher l'aide."
  exit 1
fi

# À partir d'ici, les traitements peuvent commencer
echo "Lancement des traitements..."
echo "Fichier : $CHEMIN_CSV"
echo "Type de station : $TYPE_STATION"
echo "Type de consommateur : $TYPE_CONSOMMATEUR"
[[ -n "$CENTRALE_ID" ]] && echo "Centrale spécifiée : $CENTRALE_ID" || echo "Aucune centrale spécifique."

# Simulation de traitement
echo "Traitement en cours..."
sleep 2  # Simule un traitement

echo "Traitement terminé. Résultats disponibles dans le dossier 'tmp'."
exit 0

