CXX = gcc # This is the main compiler
CXXFLAGS = -fopenmp
VPATH = test src include bin build

run: build
	@bin/Quicksort $(ARGS)

build: Quicksort.o
	@$(CXX) $(CXXFLAGS) build/Quicksort.o -o bin/Quicksort

Quicksort.o: Quicksort.cpp
	@$(CXX) $(CXXFLAGS) -I ./include -c src/Quicksort.cpp -o build/Quicksort.o

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


clean:
	echo "Cleaning..."
	find . -type f \( -name "*.o" ! -name "000-CatchMain.o" -or -name "test-node" \) -delete
	find . -type f \( -name "*.gch" -or -name "test" -or -name "samp" \) -delete
	# find . -type f -name "*.gch" -delete
	# find . -type f \( -name "*lorem.*" ! -name "lorem.txt" -or -name "lorem" \) -delete
	
	
	
	