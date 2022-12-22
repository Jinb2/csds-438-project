#!/bin/bash
#SBATCH -A sxg125_csds438 -p classc -N 2 -n 2 -c 4

echo "10:"
echo "Serial:"
./dijkstra_serial uw_10.gr
echo "OpenMp:"
./dijkstra_omp uw_10.gr

echo "100:"
echo "Serial:"
./dijkstra_serial uw_100.gr
echo "OpenMp:"
./dijkstra_omp uw_100.gr

echo "1000:"
echo "Serial:"
./dijkstra_serial uw_1000.gr
echo "OpenMp:"
./dijkstra_omp uw_1000.gr
