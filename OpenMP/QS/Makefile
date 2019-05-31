CXX = gcc # This is the main compiler
CXXFLAGS = -lm -fopenmp
VPATH = test src include bin build


# default:
#     build
#     run
run: build
	@./bin/Quicksort $(ARGS)

log: build
	@./bin/Quicksort $(ARGS) >> openmpi-quicksort-output.txt

build: Quicksort.cpp
	@$(CXX) $(CXXFLAGS) build/Quicksort.o -o bin/Quicksort
Quicksort.cpp:
	@$(CXX) $(CXXFLAGS) -I ./include -c src/Quicksort.c -o build/Quicksort.o


Sim: build
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
	@bin/Quicksort $(ARGS)
