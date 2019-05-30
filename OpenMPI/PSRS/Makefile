CXX = mpicc # This is the main compiler
CXXFLAGS = -fopenmp
VPATH = src bin build

.PHONY: build run PSRS.c

default: run
PSRS.c:
	$(CXX) $(CXXFLAGS) -I ./include -c src/PSRS.c -o build/PSRS.o

build: PSRS.c
	$(CXX) $(CXXFLAGS) build/PSRS.o -o bin/PSRS

run: build
	mpirun -np 4 ./bin/PSRS $(ARGS)
	#-DS 1000000 -SR 1
	# $(ARGS)
Sim: build
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)
	mpirun -np 4 ./bin/PSRS $(ARGS)


log: build
	./bin/PSRS $(ARGS) >> openmpi-quicksort-output.txt


