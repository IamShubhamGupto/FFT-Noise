#!/bin/bash
make
make -C analysis/extern 

SET_N=(
    64
    128
    256
    512
    1024
    2048
    4096
    8192
)

EXTERN="analysis/extern/bin/extern"
MAIN="bin/fftNoise"

RESULT_PATH="analysis/analysis.csv"

echo "N,pNoise,sNosie,fftNoise" > $RESULT_PATH

for i in "${SET_N[@]}"
do

    RESULT_MAIN=$($MAIN 2 $i -d 2>&1 > /dev/null) 
    RESULT_EXTERN=$($EXTERN $i 2>&1 > /dev/null) 

   RESULT="${i},${RESULT_EXTERN},${RESULT_MAIN}"
   echo $RESULT >> $RESULT_PATH
done

python3 analysis/plot.py