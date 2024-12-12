#!/bin/bash

# Filtrage des lignes non vides, remplacement des traits par des 0 et sélection des colonnes avec `awk`
awk -F";" '{if ($2 != "-" && $3 == "-" && $4 == "-" && $6 == "-") {gsub("-", "0", $2); gsub("-", "0", $7); gsub("-", "0", $8); print $2, $7, $8}}' data.csv > hvb.txt

