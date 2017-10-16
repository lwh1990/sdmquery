#/bin/bash

gcc -c createdata.c -I/Users/liangweihao/Documents/workspace/cdo/netcdf-4.4.1.1/build/include

gcc -o createdata createdata.o -L/Users/liangweihao/Documents/workspace/cdo/netcdf-4.4.1.1/build/lib -lnetcdf

./createdata


