#!/bin/bash
# -*- coding: utf-8 -*-

ARCHIVO="prueba 5.txt"
ARCHIVO2=prueba.csv

echo -e "esta es la primera linea modificada en ambos archivos" > "$ARCHIVO"
echo -e "esta es la primera linea modificada en ambos archivos" > $ARCHIVO2

for i in {00..19}
do
    touch code_blast2.3_$i.fasta
done

for i in `ls`
do
    echo $i
done
