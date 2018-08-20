# parallel-computing

## Assignment 1a

### Generate the random graph with 9999 vertices
python graph_generator.py --vertices 9999

### Compile with OpenMP directives
g++ -o graph.exe graph.cpp -fopenmp

### Execute the programs
./graph.exe ./graph.txt

## Example of Slurm (8 cores)
\#!/bin/bash\
\#SBATCH --nodes=1\
\#SBATCH --ntasks=8\
\#SBATCH --time=00:10:00\
\#SBATCH --partition=physical\
\#SBATCH --output=1n1c.out

\# Load required modules\
module load GCC/8.1.0\
module load binutils/2.30-GCCcore-8.1.0

\# Compile with OpenMP directives\
g++ -o graph.exe graph.cpp -fopenmp

\# Export with the number of threads desired\
\# export OMP_NUM_THREADS=8

\# Execute the programs\
\graph.exe graph.txt
