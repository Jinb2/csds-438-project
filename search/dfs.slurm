#!/bin/bash
#SBATCH -A sxg125_csds438 -p classc -N 2 -n 2 -c 4

echo "10:"
echo "Serial:"
./dfs_serial uw_10.gr
echo "OpenMp:"
./dfs_omp uw_10.gr

echo "15:"
echo "Serial:"
./dfs_serial uw_15.gr
echo "OpenMp:"
./dfs_omp uw_15.gr

echo "20:"
echo "Serial:"
./dfs_serial uw_20.gr
echo "OpenMp:"
./dfs_omp uw_20.gr
