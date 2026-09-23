#!/bin/bash


#pathfa25=~/cse29/lab/lab10/lab10-scripting-and-pokemon/pokemon
#pathfa24=~/cse29fa24/lab9-starter/pokemon
#paths=(${pathfa25} ${pathfa24})
paths=(~/MailArchive/Pokemon/*)
path=${paths[RANDOM % ${#paths[@]}]}

files=( "$path"/*.pk )
random_file="${files[RANDOM % ${#files[@]}]}"
name="${random_file##*/}"
name="${name%.pk}"
name="${name%_*}"

echo "$name's Pokemon!"
cat "$random_file"