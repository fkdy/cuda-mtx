cc=/usr/bin/g++
nvcc = /usr/bin/nvcc
# cc=/usr/bin/gcc
libs=-lcudart -lcuda
objects= main.o mtxMultiplication.o assist.o
.DEFAULT_GOAL:=mtx

mtx: $(objects)
	$(cc) -o mtx $(objects) $(libs)

assist.o: assist.cc assist.h
	$(cc) -c assist.cc

mtxMultiplication.o: mtxMultiplication.cu assist.h mtxMultiplication.h
	$(nvcc) -c mtxMultiplication.cu $(libs)

main.o: main.cc mtxMultiplication.h assist.h
	$(cc) -c main.cc $(libs)

clean:
	rm $(objects) mtx
