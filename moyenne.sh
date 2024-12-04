#!/bin/bash

if [ $# -lt 1 ]
then
	echo "nmb argument incorrect"
	exit 1
fi

for i in $@
do
	if (( i < 0 )) || (( i > 20 ))
	then
		echo "valeur incorrect"
		exit 2
	fi
done

s=0

for i in $@
do
	s=$(($s+i))
done

m=$(($s/$#))

echo "moyenne: $m"

if [ $m -lt 10 ]
then
	echo "redouble"
fi

if [ $m -ge 10 ]
then
	echo "passe"
fi


if [ $m -ge 15 ]
then
	echo "felicitation"
fi

echo $@ > note

#m=0
#for i in $@
#do
	#if [ $i -lt 0 ] || [ $i -gt 20 ]
	#then
		#echo "valeur incorrect"
		#exit 2
	#fi
	#m=$((m+i))
#done
#m=$(($m/$#))
#echo "moyenne: $m"


