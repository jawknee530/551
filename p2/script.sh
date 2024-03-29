#!/bin/bash


for i in `seq 1 2`;
do
 touch ./results/ijk20.out
 mpirun -hostfile hostfiles/10pcs ../matrixmult >> ./results/ijk20.out
done

for i in `seq 1 5`;
do
 #touch ./results/ijk16.out
 #mpirun -hostfile hostfiles/8pcs ../matrixmult >> ./results/ijk16.out
 #mpirun -hostfile 8pcs matrixmult >> script.out
done

for i in `seq 1 5`;
do
 #touch ./results/ijk12.out
 #mpirun -hostfile hostfiles/6pcs ../matrixmult >> ./results/ijk12.out
 #mpirun -hostfile 6pcs matrixmult >> script.out
done

for i in `seq 1 5`;
do
 #touch ./results/ijk8.out
 #mpirun -hostfile hostfiles/8pcs -ppn 1 ../matrixmult >> ./results/ijk8.out
 #mpirun -hostfile 8pcs -ppn 1 matrixmult >> script.out
done

for i in `seq 1 5`;
do
 #touch ./results/ijk4.out
 #mpirun -hostfile hostfiles/4pcs -ppn 1 ../matrixmult >> ./results/ijk4.out
 #mpirun -hostfile 4pcs -ppn 1 matrixmult  >> script.out
done

for i in `seq 1 5`;
do
 #touch ./results/ijk1.out
 #mpirun -n 1 ../matrixmult >> ./results/ijk1.out
 #mpirun -n 1 matrixmult >> script.out
done

#mpirun -hostfile 2pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 3pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 5pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 6pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 7pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 9pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 10pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 11pcs -ppn 1 matrixmult >> script.out
#mpirun -hostfile 7pcs matrixmult >> script.out
#mpirun -hostfile 9pcs matrixmult >> script.out

