#!/bin/bash

# Filtrage des lignes non vides et sélection des colonnes avec remplacement des "-" par "0"
awk -F";" '{
    if ($4 != "-" && $6 == "-") {
        gsub("-", "0", $0); 
        print $4, $7, $8
    }
}' data.csv > lvindiv.txt

