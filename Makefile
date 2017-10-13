CC = mpicc
INC = -I/Users/liangweihao/Documents/workspace/cdo/parallel-netcdf-1.8.1/build/include
LIB = -L/Users/liangweihao/Documents/workspace/cdo/parallel-netcdf-1.8.1/build/lib -lpnetcdf -lm
OBJ = main.o utility.o generatemeta.o


main : $(OBJ)
	$(CC) -o $@ $^ $(LIB)

main.o : main.c
	$(CC) -c -o $@ $< $(INC)

utility.o : utility.c utility.h
	$(CC) -c -o $@ $< $(INC)

generatemeta.o : generatemeta.c generatemeta.h
	$(CC) -c -o $@ $< $(INC)

clean :
	rm *.o main
