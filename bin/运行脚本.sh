#!/bin/bash

#$1... file


V2C=~/NuV2C/bin/NuV2C
BENCHMARKDIRS=`cat benchmarks.txt`

for dir in $BENCHMARKDIRS;
do
filename=main.sv
cd ${dir}
$V2C $filename --module top main_v16.c
#$V2C $filename --module top ${dir}.c

cd ..
done
