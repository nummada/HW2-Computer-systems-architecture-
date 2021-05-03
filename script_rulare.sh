#!/bin/bash

module load compilers/gnu-5.4.0
echo "Module loaded"

cd /export/home/acs/stud/m/mihaela.nuta1207/Tema2ASC

make clean
make
echo "Make done"

echo "Neoptimizat"
./tema2_neopt /export/asc/tema2/input
echo "Compare out1"
./compare out1 /export/asc/tema2/out1 0.001
echo "Compare out2"
./compare out2 /export/asc/tema2/out2 0.001
echo "Compare out3"
./compare out3 /export/asc/tema2/out3 0.001

make clean
make
echo "Make done"

echo "Optimizat"
./tema2_opt_m /export/asc/tema2/input
echo "Compare out1"
./compare out1 /export/asc/tema2/out1 0.001
echo "Compare out2"
./compare out2 /export/asc/tema2/out2 0.001
echo "Compare out3"
./compare out3 /export/asc/tema2/out3 0.001

make clean
make
echo "Make done"

echo "Blas"
./tema2_blas /export/asc/tema2/input
echo "Compare out1"
./compare out1 /export/asc/tema2/out1 0.001
echo "Compare out2"
./compare out2 /export/asc/tema2/out2 0.001
echo "Compare out3"
./compare out3 /export/asc/tema2/out3 0.001

make clean