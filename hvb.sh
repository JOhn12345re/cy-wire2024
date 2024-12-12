#!/bin/bash

# Filtrage des lignes non vides et sélection des colonnes avec `awk`
awk -F";" '{if ($2 != "-" && $3 == "-" && $4 == "-" && $6 == "-") print $2, $7, $8}' data.csv > hvb.txt


