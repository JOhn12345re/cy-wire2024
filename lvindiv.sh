#!/bin/bash

# Filtrage des lignes non vides et sélection des colonnes avec `awk`
awk -F";" '{if (  $4 != "-" && $6 == "-"   ) print $4, $7, $8}' data.csv > lvindiv.txt

