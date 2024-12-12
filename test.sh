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

# Vérifier si des combinaisons interdites sont présentes
if [[ ("$TYPE_STATION" == "hvb" && ("$TYPE_CONSOMMATEUR" == "all" || "$TYPE_CONSOMMATEUR" == "indiv")) || \
      ("$TYPE_STATION" == "hva" && ("$TYPE_CONSOMMATEUR" == "all" || "$TYPE_CONSOMMATEUR" == "indiv")) ]]; then
  echo "Erreur : La combinaison de station et consommateur n'est pas autorisée."
  echo "Les combinaisons interdites sont :"
  echo "  - hvb all"
  echo "  - hvb indiv"
  echo "  - hva all"
  echo "  - hva indiv"
  exit 1
fi

# Vérification de l'existence du fichier CSV
if [[ ! -f "$CHEMIN_CSV" ]]; then
  echo "Erreur : Fichier CSV introuvable : $CHEMIN_CSV"
  echo "Utilisez l'option -h pour afficher l'aide."
  exit 1
fi

# Traitement du fichier CSV
echo "Traitement en cours sur le fichier CSV..."

# Vérification de la variable TYPE_STATION et TYPE_CONSOMMATEUR
if [[ "$TYPE_STATION" == "hva" && "$TYPE_CONSOMMATEUR" == "comp" ]]; then
    # Traitement avec awk pour "hva"
    awk -F";" '{
        if ($3 != "-" && $4 == "-" && $6 == "-") {
            gsub("-", "0", $3);
            gsub("-", "0", $7);
            gsub("-", "0", $8);
            print $3, $7, $8;
        }
    }' "$CHEMIN_CSV" > hva.txt
fi

if [[ "$TYPE_STATION" == "hvb" && "$TYPE_CONSOMMATEUR" == "comp" ]]; then
    # Traitement avec awk pour "hvb"
    awk -F";" '{
        if ($2 != "-" && $3 == "-" && $4 == "-" && $6 == "-") {
            gsub("-", "0", $2);
            gsub("-", "0", $7);
            gsub("-", "0", $8);
            print $2, $7, $8;
        }
    }' "$CHEMIN_CSV" > hvb.txt
fi

if [[ "$TYPE_STATION" == "lv" ]]; then
    # Traitement avec awk pour "lv"
    
    if [[ "$TYPE_CONSOMMATEUR" == "indiv" ]]; then
        awk -F";" '{
            # Remplacement des "-" par "0" dans toutes les colonnes
            gsub("-", "0", $0); 
            
            # Vérification des conditions sur les colonnes 4 et 6
            if ($4 != "0" && $5 == "0") {
                # Impression des colonnes 4, 7 et 8
                print $4, $7, $8
            }
        }' "$CHEMIN_CSV" > lvindiv.txt
    fi

    if [[ "$TYPE_CONSOMMATEUR" == "all" ]]; then
        awk -F";" '{
            # Remplacement des "-" par "0" dans toutes les colonnes
            gsub("-", "0", $0); 
            
            if ($4 != "0") {
                # Impression des colonnes 4, 7 et 8
                print $4, $7, $8
            }
        }' "$CHEMIN_CSV" | tail -n +2 > lvall.txt
    fi

    if [[ "$TYPE_CONSOMMATEUR" == "comp" ]]; then
        awk -F";" '{
            # Remplacement des "-" par "0" dans toutes les colonnes
            gsub("-", "0", $0); 
            
            # Vérification de la condition et impression des colonnes souhaitées
            if ($4 != "0" && $6 == "0") {
                print $4, $7, $8
            }
        }' "$CHEMIN_CSV" > lvcomp.txt
    fi
fi

