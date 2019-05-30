CXX = mpicc # This is the main compiler
CXXFLAGS = -fopenmp
VPATH = src bin build

.PHONY: build run QS.c

default: run
QS.c:
	@$(CXX) $(CXXFLAGS) -I ./include -c src/QS.c -o build/QS.o

build: QS.c
	@$(CXX) $(CXXFLAGS) build/QS.o -o bin/QS

run: build
	@mpirun -np 4 ./bin/QS $(ARGS)
	#-DS 1000000 -SR 1
	# $(ARGS)

Sim: build
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)
	@mpirun -np 4 ./bin/QS $(ARGS)


log: build
	./bin/QS $(ARGS) >> openmpi-quicksort-output.txt


