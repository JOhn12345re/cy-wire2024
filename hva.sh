#!/bin/bash

# Filtrage des lignes non vides et sélection des colonnes avec `awk`, remplacement des traits par des 0
awk -F";" '{if ($3 != "-" && $4 == "-" && $6 == "-") {gsub("-", "0", $3); gsub("-", "0", $7); gsub("-", "0", $8); print $3, $7, $8}}' data.csv > hva.txt

