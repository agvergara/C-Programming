#!/bin/bash
cont=1
for i
do
  if test $cont -eq $#
  then
    a="."$i
  else
    file=$i
    cont=$(($cont+1))
  fi
done

cd $a
cont=1

for i
do
  if test $cont -ne $#
  then
    while read fichero
    do
    photo=`find | egrep *$file`
    lengthname=$((${#photo}-${#file}))
    echo $photo2
    echo "$photo: =======> $photo"
    done < $i
    cont=$(($cont+1))
    fi
done
