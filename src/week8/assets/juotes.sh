#!/bin/bash
file=~/Quotes/Joe\ Politz
mapfile -t linesArray < "$file"

echo  "\"${linesArray[RANDOM % ${#linesArray[@]}]#*-|}\" - ${file##*/}"