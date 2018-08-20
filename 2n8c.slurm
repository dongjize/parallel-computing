#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --time=00:10:00
#SBATCH --partition=physical
#SBATCH --output=2n8c.out

# Load required modules
module load GCC/8.1.0
module load binutils/2.30-GCCcore-8.1.0

# Compile with OpenMP directives
g++ -o graph.exe graph.cpp -fopenmp

# Export with the number of threads desired
# export OMP_NUM_THREADS=8

# Execute the programs
./graph.exe ./graph.txt