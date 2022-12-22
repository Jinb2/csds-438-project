#!/bin/bash
#SBATCH -A sxg125_csds438 -p classc -N 2 -n 2 -c 4

echo "10:"
echo "Serial:"
./bfs_serial uw_10.gr
echo "OpenMp:"
./bfs_omp uw_10.gr

echo "15:"
echo "Serial:"
./bfs_serial uw_15.gr
echo "OpenMp:"
./bfs_omp uw_15.gr

echo "100:"
echo "Serial:"
./bfs_serial uw_100.gr
echo "OpenMp:"
./bfs_omp uw_100.gr
