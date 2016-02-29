#!/bin/bash

rm script.out
touch script.out

mpirun -n 1 parallel >> script.out
mpirun -n 2 parallel >> script.out
mpirun -hostfile 2pcs parallel >> script.out
mpirun -hostfile 3pcs parallel >> script.out
mpirun -hostfile 4pcs parallel >> script.out
mpirun -hostfile 5pcs parallel >> script.out
mpirun -hostfile 6pcs parallel >> script.out
mpirun -hostfile 7pcs parallel >> script.out
mpirun -hostfile 8pcs parallel >> script.out
mpirun -hostfile 9pcs parallel >> script.out
mpirun -hostfile 10pcs parallel >> script.out

