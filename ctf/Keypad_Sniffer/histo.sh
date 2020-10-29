#!/bin/bash

inputFile=$1
tmpFile=tmp_file

cat $inputFile |sort -u > $tmpFile

while read line
do
   var=$(grep $line $inputFile -c)
   echo "$line: $var occurences"
done < $tmpFile
