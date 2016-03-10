#!/bin/bash


mpirun -n 1 parallel >> timings
mpirun -hostfile 2pcs -ppn 1 parallel >> timings
mpirun -hostfile 8pcs -ppn 1 parallel >> timings
mpirun -hostfile 7pcs parallel >> timings
mpirun -hostfile 10pcs parallel >> timings


