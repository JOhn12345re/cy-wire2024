#!/bin/bash


cut -d";" -f2,5,7,8 data.csv > hvb.csv

# Filtrage des lignes non vides et sélection des colonnes avec `awk`
awk -F";" '{if ($1 != "-") print $1 ,$3 ,$4}' hvb.csv > hvb1.txt
cut -d";" -f1,3,4 hvb1.csv > hvb2.csv

