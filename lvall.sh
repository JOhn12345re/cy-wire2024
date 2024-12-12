#!/bin/bash
awk -F";" '{
 # Remplacement des "-" par "0" dans toutes les colonnes
    gsub("-", "0", $0); 
    
# Filtrage des lignes non vides et sélection des colonnes avec `awk`
if (  $4 != "-"   ) print $4, $7, $8}' data.csv > lvall.txt

