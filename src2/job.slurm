#!/bin/bash
#SBATCH -A sxg125_csds438 -p classc -N 2 -n 2 -c 4

echo "10:"
echo "Serial:"
./graph uw_10.gr
echo "OpenMp:"
./graph_omp uw_10.gr

echo "15:"
echo "Serial:"
./graph uw_15.gr
echo "OpenMp:"
./graph_omp uw_15.gr

echo "100:"
echo "Serial:"
./graph uw_100.gr
echo "OpenMp:"
./graph_omp uw_100.gr
