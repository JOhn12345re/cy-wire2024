#!/bin/bash

verif_note(){
	if [ $1 -lt 0 ] || [ $1 -gt 20 ]
	then
		echo "$2"
		exit 2
	fi
}

while getopts ":ma" opt
do
	case $opt in
	m) 
	note=" "

	for i in `seq 2 $#`
	do
		verif_note ${!i} "valeur incorrect"
		note="$note ${!i}"
	done
	gcc -o exe myn.c
	a=`./exe $note`
	echo "moyenne: $a"
	;;
	a) 
	n=0
	for i in `seq 2 $#`
	do
		n=$((n+1))
		echo "note $n: ${!i}"
	done
	;;
	?) echo "erreur"
	;;
	esac
done

if [ $# -lt 1 ]
then
	echo "nmb argument incorrect"
	exit 1
fi






