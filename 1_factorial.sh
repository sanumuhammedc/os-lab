#!/bin/sh

echo "Enter number to find factorial"
read NUMBER

FACTORIAL=1

while [ $NUMBER -gt 1 ]
do
   FACTORIAL=$((NUMBER * FACTORIAL))
   NUMBER=$((NUMBER - 1))
done

echo "Factorial is $FACTORIAL"	
