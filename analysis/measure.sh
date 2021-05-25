#!/bin/bash
make  

SET_N=(
    8
    16
    32
    64
    128
    256
    512
    1024
    2048
    4096
)

PROGRAM=fftNoise
PROGRAM_DIR=bin

RESULT_PATH=analysis/analysis.csv

echo "type,dt,N" > $RESULT_PATH

for i in "${SET_N[@]}"
do
   DT=$($PROGRAM_DIR/$PROGRAM 2 $i -d $ARGS 2>&1 > /dev/null)
   RESULT="${PROGRAM},${DT},${i}"
   echo $RESULT >> $RESULT_PATH
done

# python analysis/plot.py