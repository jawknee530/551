#!/bin/bash

rm script.out
touch script.out

for i in `seq 1 5`;
do
  mpirun -n 1 a.out >> script.out
done
#mpirun -hostfile 2pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 3pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 4pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 5pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 6pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 7pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 8pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 9pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 10pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 11pcs -ppn 1 parallel >> script.out
#mpirun -hostfile 6pcs parallel >> script.out
#mpirun -hostfile 7pcs parallel >> script.out
#mpirun -hostfile 8pcs parallel >> script.out
#mpirun -hostfile 9pcs parallel >> script.out
#mpirun -hostfile 10pcs parallel >> script.out

