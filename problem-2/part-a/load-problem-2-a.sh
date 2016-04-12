#!/bin/bash
RUNS=$1

mkdir -p csv/${RUNS}runs

for ((i=1; i<=$RUNS; i++))
do
  # print delays from c program 
  ./timer_usleep_2  5 1000 ${i} > csv/"${RUNS}"runs/run"${i}".csv &
  
  # open permissions of all files 
  sudo chown -R ntpstudent:ntpstudent ./csv/ 
done
