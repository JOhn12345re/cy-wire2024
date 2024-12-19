#!/bin/bash

if [[ $# -lt 2 ]]; then
	cat $1 | sort -n -k3 > "sort.txt"
	head "sort.txt" > "head.txt" 
	tail "sort.txt" > "tail.txt"
	cat "tail.txt" "head.txt" > "lv_minmax.txt"
fi
