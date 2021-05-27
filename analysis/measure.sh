#!/bin/bash
make -C analysis/extern 

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

PROGRAM=extern
PROGRAM_DIR=analysis/extern/bin

RESULT_PATH=analysis/analysis.csv

echo "N,perlin_noise,simplex_noise,fft_noise" > $RESULT_PATH

for i in "${SET_N[@]}"
do
   DT=$($PROGRAM_DIR/$PROGRAM $i $ARGS 2>&1 > /dev/null)
   RESULT="${DT}"
   echo $RESULT >> $RESULT_PATH
done

python analysis/plot.py || python3 analysis/plot.py