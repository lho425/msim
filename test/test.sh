#!/bin/bash

cd `dirname $0`
../map2Ccode.sh map.txt mywalldata.c &&


gcc -Wall -O3 main.c ../msim.c mywalldata.c  -o msim &&

./msim

