#!/bin/bash

# Traitement avec awk pour filtrer et remplacer les traits "-" par "0"
awk -F";" '{
    # Remplacement des "-" par "0" dans toutes les colonnes
    gsub("-", "0", $0); 
    
    if ($4 != "0") {
        # Impression des colonnes 4, 7 et 8
        print $4, $7, $8
    }
}' data.csv | tail -n +2 > lvall.txt

