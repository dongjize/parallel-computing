#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=8
#SBATCH --time=00:10:00
#SBATCH --partition=physical
#SBATCH --output=1n8c.out

# Load required modules
module load GCC/4.9.2


# Compile with OpenMP directives
gcc -o3 -o graph.exe graph.cpp -lstdc++ -fopenmp

# Export with the number of threads desired
# export OMP_NUM_THREADS=8

# Execute the programs
./graph.exe ./graph.txt
