#!/bin/bash

rm script.out
touch script.out

mpirun -n 1 parallel >> script.out
mpirun -n 2 parallel >> script.out
mpirun -hostfile 4cores parallel >> script.out
mpirun -hostfile 6cores parallel >> script.out
mpirun -hostfile 8cores parallel >> script.out
mpirun -hostfile 10cores parallel >> script.out
mpirun -hostfile 12cores parallel >> script.out
mpirun -hostfile 14cores parallel >> script.out
mpirun -hostfile 16cores parallel >> script.out
mpirun -hostfile 18cores parallel >> script.out
mpirun -hostfile 20cores parallel >> script.out

