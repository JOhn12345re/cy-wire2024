#!/bin/bash

# Filtrage des lignes non vides et sélection des colonnes avec `awk`
awk -F";" '{if ($3 != "-" && $4 == "-" && $6 "-"   ) print $3, $7, $8}' data.csv > hva.csv

