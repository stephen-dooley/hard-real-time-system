#!/bin/bash
RUNS=$1

# -p flag creetes all sub directories if they don't exit
mkdir -p csv//${RUNS}runs

for (( i=1; i<=$RUNS; i++))
do

 ./timer_FIFO_loop 5 1000 ${i} > csv/"${RUNS}"runs/run"${i}".csv &

 # open permissions of all files
 sudo chown -R ntpstudent:ntpstudent ./csv/
done

