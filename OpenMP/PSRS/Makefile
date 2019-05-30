
CXX = gcc# This is the main compiler
CXXFLAGS = -fopenmp
VPATH = test src include bin build


# default:
#     build
#     run
run: build
	@./bin/PSRS $(ARGS)

log: build
	@./bin/PSRS $(ARGS) >> openmpi-quicksort-output.txt

build: PSRS.cpp
	@$(CXX) $(CXXFLAGS) build/PSRS.o -o bin/PSRS -lm
PSRS.cpp:
	@$(CXX) $(CXXFLAGS) -I ./include -c src/PSRS.c -o build/PSRS.o

Sim: build
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)
	@./bin/PSRS $(ARGS)


