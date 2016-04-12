#!/bin/bash
RUNS=$10
NICE=$2
mkdir -p nicecsv/${RUNS}runs

for ((i=1; i<=$RUNS; i++))
do
  echo "yho"
  # apply nice to some timers
  if ["${i}" -lt "${NICE}"]
  then
    echo "yo"
  fi
  # print delays from c program 
  ./timer_usleep_2  5 1000 ${i} > /nicecsv/"${RUNS}"runs/run"${i}".csv &
  
  # open permissions of all files 
  sudo chown -R ntpstudent:ntpstudent ./nicecsv/  
done
