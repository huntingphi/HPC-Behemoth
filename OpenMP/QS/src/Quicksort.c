#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "omp.h"

#include "../include/Quicksort.h"


//int lenArr = 262144000; // 262144000 = 1000 MBytes = 1 GByte
//int numthreads = omp_get_max_threads();

/* -----------------------------------------------------------------------
   Tests the result
 * ----------------------------------------------------------------------- */
void testit(int *v, int * nelements) {
  register int k;
	int not_sorted = 0;
  for (k = 0; k < (*nelements) - 1; k++)
    if (v[k] > v[k + 1]) {
      not_sorted = 1;
      break;
    }
    if (not_sorted)
    {
    printf("Array NOT sorted.\n");
        exit(1);
    }

//   if (not_sorted)
//     printf("Array NOT sorted.\n");
// 	else
//     printf("Array sorted.\n");
}

/* -----------------------------------------------------------------------
   Sets randomly the values for the array
 * ----------------------------------------------------------------------- */
void initialize(int *v, int seed, int nelements) {
  unsigned i;
   srandom(seed);
   for(i = 0; i < nelements; i++)
     v[i] = (int)random()%1000;
}
/////////////////////////////////



void quickSort(int* arr, int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

  	/* PARTITION PART */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}

	/* RECURSION PART */
	if (left < j){ quickSort(arr, left, j);  }
	if (i< right){ quickSort(arr, i, right); }
}





// Comparator used in qsort()
int cmpfunc (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}



int main(int argc, char **argv){

	int nelements= 1000000;
    int seed=1;
	int np = 1;
    if (argc==2){
        nelements = atoi(argv[1]);
    }else if (argc==3){
        nelements = atoi(argv[1]);
        seed = atoi(argv[2]);
    }else if (argc ==4){
		nelements = atoi(argv[1]);
        seed = atoi(argv[2]);
		np = atoi(argv[3]);
	}
	int minMum = 1;
	int maxNum = nelements;
	int maxNumbersDisplayed = 30;

	double startTime, stopTime;


	int* arr1;
	int* arr2;
	int* arr3;
	arr1 = (int*) malloc(nelements*sizeof(int));
	arr2 = (int*) malloc(nelements*sizeof(int));
	arr3 = (int*) malloc(nelements*sizeof(int));


	//printf("--------------------------------------------------");
	//printf("Info about the program: \n");
	//printf("Datatype of the array: %p", typeof() );
	//printf("Positions in the array: %d", typeof(arr1) );
//	printf("\nSize of the array (aprox.): %lu MBytes \n", (nelements*sizeof(int)/(1024*1024)) );
//	printf("TOTAL MEMORY ALLOCATED:  3 x array = (aprox.): %lu MBytes \n\n", (nelements*sizeof(int)/(1024*1024))*3 );
	//printf("-------------------------------------------------- \n\n");



	// Initialise the array with random numbers
	int i;
//	srand(5); // seed
//	printf("Initializing the arrays with random numbers...\n");
//	for (i=0; i<nelements; i++){
		// RAND_MAX = 2147483647 = INT_MAX
		// printf("RAND_MAX %u \n", RAND_MAX );
//		arr1[i] = minMum+(rand()%maxNum);
//		arr2[i] = arr1[i];
//		arr3[i] = arr1[i];
		//printf("%d \n", arr1[i] );
//	}
    initialize(arr1,seed,nelements);
//    initialize(arr2,seed,nelements);
//    initialize(arr3,seed,nelements);
    	for (i=0; i<nelements; i++){
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
	}

    //	printf("Initialization complete\n");




	if( nelements <= maxNumbersDisplayed ){
		printf("\n\nArray BEFORE sorting: \n");
		for( i = 0 ; i < nelements; i++ )
		{
			printf("%d ", arr1[i]);
		}
		printf("\n\n\n");
	}


//	printf("\nSorting with serial 'qsort' function of 'stdlib.h' ..."); fflush(stdout);
	startTime = omp_get_wtime();
	qsort(arr1, nelements, sizeof(int), cmpfunc);
	stopTime = omp_get_wtime();


	if( nelements <= maxNumbersDisplayed ){
		for( i = 0 ; i < nelements; i++ )
		{
			printf("%d ", arr1[i]);
		}

	}
//	printf("\nSorted in (aprox.): %f seconds \n\n", (double)(stopTime-startTime)/CLOCKS_PER_SEC);




//	printf("\nSorting with custom serial QuickSort..."); fflush(stdout);
	startTime = omp_get_wtime();
	quickSort(arr2, 0, nelements-1);
	stopTime = omp_get_wtime();


	if( nelements <= maxNumbersDisplayed ){
		for( i = 0 ; i < nelements; i++ )
		{
			printf("%d ", arr2[i]);
		}
	}
//	printf("\nSorted in (aprox.): %f seconds \n\n", (double)(stopTime-startTime)/CLOCKS_PER_SEC);



//	printf("\nSorting with custom PARALLEL QuickSort... "); fflush(stdout);
    int nThreads = np;
	startTime = omp_get_wtime();
	quickSort_parallel(arr3, nelements, nThreads);
	stopTime = omp_get_wtime();
    double duration = stopTime - startTime;
    printf("OpenMP-QS,%d,%d,%f\n",nThreads,nelements,duration);

	if( nelements <= maxNumbersDisplayed ){
		for( i = 0 ; i < nelements; i++ )
		{
			printf("%d ", arr3[i]);
		}
	}
//	printf("\nSorted in (aprox.): %f seconds \n\n", (stopTime-startTime));




//	printf("\nChecking if the results are correct...\n");
//	typedef enum { false, true } bool;
//	bool correctResult;
//
//	correctResult=true;
//	i = 0;
//	while( (correctResult==true) && (i<nelements) )
//	{
//		if(arr1[i]!=arr2[i]) { correctResult=false; }
//		i++;
//	}
//	if(correctResult==true){
//		printf("The result with 'custom serial QuickSort' is CORRECT\n");
//	}else{
//		printf("The result with 'custom serial QuickSort' is ¡¡INCORRECT!!\n");
//	}
//
//	correctResult = true;
//	i = 0;
//	while( (correctResult==true) && (i<nelements) )
//	{
//		if(arr1[i]!=arr3[i]) { correctResult=false; }
//		i++;
//	}
//	if(correctResult==true){
//		printf("The result with 'custom PARALLEL QuickSort' is CORRECT\n\n");
//	}else{
//		printf("The result with 'custom PARALLEL QuickSort' is ¡¡INCORRECT!!\n");
//	}
//
//
//
//
//	printf("\n\n");

	free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}