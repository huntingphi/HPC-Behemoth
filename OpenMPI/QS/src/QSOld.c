#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
// #include <openmp.h>

//#define N 2000000
//#define X 1000

void quicksort(int *, int, int);
int partition(int *, int, int);
int choosePivot(int *, int, int);
void swap(int *, int *);


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

int main(int argc, char ** argv)
{
  MPI_Init(&argc, &argv);
    // printf("no args: %d\n",argc);
    // printf("arg1 %s\n",argv[1]);
    // printf("arg2 %s\n",argv[2]);
    int nelements,seed;
    // int N;//atoi(argv[1]);
    // int X = atoi(argv[2]);
  int rank, size, pivot, partner, recvSize;
  double start, end;
  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // srandom(1);
//  srand(123456 + 10000*rank);
	nelements= 1000000;
    seed=1;
    if (argc==2){
        nelements = atoi(argv[1]);
        seed = 1;
    }else if (argc==3){
        nelements = atoi(argv[1]);
        seed = atoi(argv[2]);
    }



  int * newArr;
  int * arr = (int *) malloc(sizeof(int)*nelements/size);
  int * recvBuffer = (int *) malloc(sizeof(int)*nelements/size);

  int i, j;
  for(i = 0; i < nelements/size; i++)
    arr[i] = random()%1000;
  //  initialize(arr,1,nelements/size);

  if(rank == 0)
  {
    start = MPI_Wtime();
    pivot = choosePivot(arr, 0, nelements/size-1);
    // printf("The pivot is %d\n", pivot);
  }

  MPI_Bcast(&pivot, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //Assume that the number of processes is a power of 2

  int storeIdx = 0;
  int arrSize = nelements/size;

  for(partner = size/2; partner > 0; partner = partner >> 1)
  {
    storeIdx = 0;
    for(i = 0; i < arrSize; i++)
    {
      if(arr[i] < pivot)
      {
        swap(&arr[i], &arr[storeIdx]);
        storeIdx++;
      }
    }
    // printf("storeIdx = %d in process %d\n", storeIdx, rank);
//0...7 8...15 16/2 = 8
//
//rank / (size/partner)
//0 vs 1
//
//0..3   4..7   8..11 12..15 16/4 = 4
//lower upper   lower upper
//0      1       2     3
    int flag = 0;
    MPI_Request request, requestSend;
    if( (rank / partner) % 2 == 0)
    {

      // printf("rank + partner is %d\n", rank + partner);

      int sendVal = arrSize-storeIdx;
      recvSize = 0;
      MPI_Isend(&sendVal, 1, MPI_INT, rank+partner, partner+size, MPI_COMM_WORLD, &requestSend);
      MPI_Irecv(&recvSize, 1, MPI_INT, rank+partner, partner+size, MPI_COMM_WORLD, &request);
      MPI_Wait(&request, &status);


      if(arrSize-storeIdx > 0)
      {
        MPI_Isend(arr+storeIdx, arrSize - storeIdx, MPI_INT, rank + partner, partner,MPI_COMM_WORLD, &requestSend);
      }

      // printf("recvsize is %d in process %d\n", recvSize, rank);

      if(recvSize > 0)
      {
        free((void *) recvBuffer);
        recvBuffer = (int *) malloc(sizeof(int)*recvSize);

        MPI_Irecv(recvBuffer, recvSize, MPI_INT, rank + partner, partner,
                         MPI_COMM_WORLD, &request);

        MPI_Wait(&request, &status);
      }
    }
    else
    {
      int sendVal = storeIdx;
      recvSize = 0;
      MPI_Isend(&sendVal, 1, MPI_INT, rank-partner, partner+size, MPI_COMM_WORLD, &requestSend);
      MPI_Irecv(&recvSize, 1, MPI_INT, rank-partner, partner+size, MPI_COMM_WORLD, &request);
      MPI_Wait(&request, &status);
      // printf("rank - size is %d\n", rank - partner);

      if(storeIdx > 0)
      {
        MPI_Isend(arr, storeIdx, MPI_INT, rank - partner, partner, MPI_COMM_WORLD, &requestSend);
      }

      // printf("recvsize is %d in process %d\n", recvSize, rank);
      if(recvSize > 0)
      {
        free((void *) recvBuffer);
        recvBuffer = (int *) malloc(sizeof(int)*recvSize);

        MPI_Irecv(recvBuffer, recvSize, MPI_INT, rank - partner, partner,
                         MPI_COMM_WORLD, &request);

        MPI_Wait(&request, &status);
      }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if(recvSize > 0)
    {
      //Merge arrays
      if((rank / partner) % 2 == 0) //Keep smaller elements
      {
        newArr = (int *) malloc(sizeof(int)*(recvSize+storeIdx));
        for(i = 0; i < storeIdx; i++)
          newArr[i] = arr[i];
        for(j = 0, i = storeIdx; i < recvSize+storeIdx; i++, j++)
          newArr[i] = recvBuffer[j];
        free((void *) arr);
        arr = newArr;
        newArr = NULL;
        arrSize = recvSize+storeIdx;
      }
      else  //Keep larger elements
      {
        newArr = (int *) malloc(sizeof(int)*(recvSize+(arrSize-storeIdx)));
        for(j = 0, i = storeIdx; i < arrSize; i++, j++)
          newArr[j] = arr[i];
        for(j = 0, i = arrSize-storeIdx; i < recvSize+(arrSize-storeIdx); i++, j++)
          newArr[i] = recvBuffer[j];
        free((void *) arr);
        arr = newArr;
        newArr = NULL;
        arrSize = recvSize+(arrSize-storeIdx);
      }
    }
    else
    {
      arrSize = 0;
    }

    if(rank % partner == 0)
    {
      pivot = choosePivot(arr, 0, arrSize-1);

      for(i = 1; i < partner; i++)
        MPI_Send(&pivot, 1, MPI_INT, rank+i, partner+1, MPI_COMM_WORLD);
    }
    else
    {
      MPI_Recv(&pivot, 1, MPI_INT, partner*(rank/partner), partner+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

  }

  if(arrSize > 0)
    quicksort(arr, 0, arrSize-1);

  int * sizeArr, * fullArr, * displacement;
  if(rank == 0)
  {
    sizeArr = (int *) malloc(sizeof(int)*size);
    fullArr = (int *) malloc(sizeof(int)*nelements);
    displacement = (int *) malloc(sizeof(int)*size);
  }

  MPI_Gather(&arrSize, 1, MPI_INT, sizeArr, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if(rank == 0)
  {
    i = 0;
    displacement[0] = 0;
    // printf("displacement[%d] = %d\n", i, displacement[i]);
    //Perform a scan on sizeArr to determine the displacement of each data location.
    for(i = 1; i < size; i++)
    {
      displacement[i] = sizeArr[i-1] + displacement[i-1];
      // printf("displacement[%d] = %d\n", i, displacement[i]);
    }
  }

  MPI_Gatherv(arr, arrSize, MPI_INT, fullArr, sizeArr, displacement, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  if(arrSize > 0)
    free((void *) arr);

  if(rank == 0)
  {
//    for(i = 0; i < nelements; i++)
//      printf("%d ", fullArr[i]);
    end = MPI_Wtime();
    double duration = end-start;
    printf("OpenMPI-QS,%d,%d,%f\n",size,nelements,duration);


    free((void *) fullArr);
    free((void *) sizeArr);
    free((void *) displacement);
  }

  MPI_Finalize();

  return 0;
}

void quicksort(int * arr, int lo, int hi)
{
  if(lo < hi)
  {
    int p = partition(arr, lo, hi);
    quicksort(arr, lo, p - 1);
    quicksort(arr, p + 1, hi);
  }
}

int partition(int * arr, int lo, int hi)
{
  int i;
  int pivotIdx = choosePivot(arr, lo, hi);
  int pivotVal = arr[pivotIdx];

  swap(&arr[pivotIdx], &arr[hi]);

  int storeIdx = lo;

  for(i = lo; i < hi; i++)
  {
    if(arr[i] < pivotVal)
    {
      swap(&arr[i], &arr[storeIdx]);
      storeIdx++;
    }
  }

  swap(&arr[storeIdx], &arr[hi]);
  return storeIdx;
}

void swap(int * x, int * y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

//Select the median of arr[lo], arr[hi], and arr[(lo+hi)/2]
int choosePivot(int * arr, int lo, int hi)
{
  int mid = (lo+hi)/2;

  int temp;
  if(arr[lo] > arr[hi])
  {
    temp = lo;
    lo = hi;
    hi = temp;
  }
  if(arr[mid] < arr[lo])
  {
    temp = mid;
    mid = lo;
    lo = temp;
  }
  if(arr[hi] < arr[mid])
  {
    temp = mid;
    mid = hi;
    hi = temp;
  }
  return arr[mid];
}
