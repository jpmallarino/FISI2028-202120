#!/bin/bash
# -*- coding: utf-8 -*-

NUM_TRIALS=100
APP1_NAME=""
APP1_INT=""
APP1_FILE=""

if [ $# -eq 0 ]
then
  echo -e "Please input the following information."
  echo -e "  \033[33mHint:\033[0m you can also run as e.g. `basename $0` prueba1 10 prueba1.dat"
  read -p 'Experiment name? ' APP1_NAME
  read -p 'Max value? ' APP1_INT
  read -p 'Data filename? ' APP1_FILE
elif [ ! $# -eq 3 ]
then
  echo -e "Usage: The command needs a <name>, a positive integer and a filename as an argument\n\te.g. `basename $0` prueba1 10 prueba1.dat" >&2; exit 1
else
  APP1_NAME=$1
  APP1_INT=$2
  APP1_FILE=$3
fi

re="^[0-9]+$"
if ! [[ $APP1_INT =~ $re ]]
then
  echo "Error: Max value [=$APP1_INT] not a positive integer number" >&2; exit 1
fi

[ -f $APP1_FILE ] && echo "File: <$APP1_FILE> exists and will be overwritten" 1>&2

printf "Checks passed, running the calculations\n" >&2
printf "Process id=%d\n" $$

echo -e "experiment\tdata" > $APP1_FILE
for it in `seq $NUM_TRIALS`
do
    num=`od -An -N1 -i /dev/random`
    if [ $num -gt $APP1_INT ]
    then
        let num=$APP1_INT
    fi
    printf "%s\t%d\n" $APP1_NAME $num >> $APP1_FILE
done

exit 0
