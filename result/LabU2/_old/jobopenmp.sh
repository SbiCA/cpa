#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .

echo OMP_NUM_THREADS=1
OMP_NUM_THREADS=1 ./primo_grande

echo OMP_NUM_THREADS=2
OMP_NUM_THREADS=2 ./primo_grande

echo OMP_NUM_THREADS=4
OMP_NUM_THREADS=4 ./primo_grande

echo OMP_NUM_THREADS=8
OMP_NUM_THREADS=8 ./primo_grande

echo OMP_NUM_THREADS=16
OMP_NUM_THREADS=16 ./primo_grande

echo OMP_NUM_THREADS=32
OMP_NUM_THREADS=32 ./primo_grande

echo OMP_NUM_THREADS=64
OMP_NUM_THREADS=64 ./primo_grande

