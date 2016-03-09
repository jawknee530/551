#!/bin/bash

rm script.out
touch script.out

mpirun -n 1 parallel >> script.out
mpirun -hostfile 2pcs -ppn 1 parallel >> script.out
mpirun -hostfile 3pcs -ppn 1 parallel >> script.out
mpirun -hostfile 4pcs -ppn 1 parallel >> script.out
mpirun -hostfile 5pcs -ppn 1 parallel >> script.out
mpirun -hostfile 6pcs -ppn 1 parallel >> script.out
mpirun -hostfile 7pcs -ppn 1 parallel >> script.out
mpirun -hostfile 8pcs -ppn 1 parallel >> script.out
mpirun -hostfile 9pcs -ppn 1 parallel >> script.out
mpirun -hostfile 10pcs -ppn 1 parallel >> script.out
mpirun -hostfile 11pcs -ppn 1 parallel >> script.out
mpirun -hostfile 6pcs parallel >> script.out
mpirun -hostfile 7pcs parallel >> script.out
mpirun -hostfile 8pcs parallel >> script.out
mpirun -hostfile 9pcs parallel >> script.out
mpirun -hostfile 10pcs parallel >> script.out

