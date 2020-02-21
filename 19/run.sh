#! /bin/bash

echo num_trials: $1

for (( i = 1; i <= 8192; i *= 2 ))
do
  ./19.o $i $1
done
