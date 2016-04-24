/* File matrixmulti.c
 * Name: Jon Allen
 * Class: CSCI 551
 * Assignement 2
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <mpi.h>
using namespace std;

void Solveijk (int *A, int *B, int *C, int n, int comm_sz);
void Solveikj (int *A, int *B, int *C, int n, int comm_sz);
void Solvekij (int *A, int *B, int *C, int n, int comm_sz);

int main(int argc, char *argv[]) {
  //set up variables
  double t_start, t_finish, t_elapsed;
  int my_rank, comm_sz;
  string form;
  string flag;
  int n;
  int iform; //1 ijk, 2 ikj, 3 kij
  int *A, *B, *C, *my_A, *my_C, *my_B;
  int data[2];

  //start mpi
  MPI_Init(NULL, NULL);
  //get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //get comm size
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  //Output for timing runs
  if(my_rank == 0) {
    cout << "--------------------------------------" << endl;
    cout << " Comm_size: " << comm_sz << endl;
  }

  if(my_rank == 0) {
    //get user input
    cin >> form;
    cin >> flag;
    cin >> n;

    //set up matrices memory
    A = (int *)calloc(n*n,sizeof(int));
    B = (int *)calloc(n*n,sizeof(int));
    C = (int *)calloc(n*n,sizeof(int));
    my_A = (int *)calloc((n/comm_sz)*n,sizeof(int));
    if(form != "kij") {
      my_C = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }
    else {
      my_C = (int *)calloc(n*n,sizeof(int));
      my_B = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }

    //zero out C
    for(int i = 0; i < n*n; i++) {
      C[i] = 0;
    }

    //timing run output
    cout << " Form: " << form << endl;

    if(flag == "I") {
      for(int i = 0; i < n*n; i++) {
        cin >> A[i];
      }
      for(int i = 0; i < n*n; i++) {
        cin >> B[i];
      }
    }
    //fill A and B with random data if R
    else if(flag == "R") {
      srand(time(NULL));
      for(int i = 0; i < n*n; i++) {
        A[i] = rand() % 100;
      }
      for(int i = 0; i < n*n; i++) {
        B[i] = rand() % 100;
      }
    }

    //enumerate the flags to make sending easier
    if(form == "ijk") {
      iform = 1;
    }
    else if(form == "ikj"){
      iform = 2;
    }
    else if(form == "kij"){
      iform = 3;
    }
    //set up data array to broadcast n and form
    data[0] = n;
    data[1] = iform;
  }

  //start barrier and timing
  MPI_Barrier(MPI_COMM_WORLD);
  t_start = MPI_Wtime();

  //broadcast n and form to everyone
  MPI_Bcast(&data, 2, MPI_INT, 0, MPI_COMM_WORLD);

  //set up not 0s myA, B, C and local n and form
  if(my_rank != 0) {
    n = data[0];
    my_A = (int *)calloc((n/comm_sz)*n,sizeof(int));
    iform = data[1];

    if(iform != 3) { //not form kij
      B = (int *)calloc(n*n,sizeof(int));
      my_C = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }
    else { //form kij
      my_C = (int *)calloc(n*n,sizeof(int));
      my_B = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }
  }

  //Broadcast and scatter B & A
  if(iform !=3) { //not form kij
    MPI_Bcast(B, n*n, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, (n/comm_sz)*n, MPI_INT, my_A, (n/comm_sz)*n,
        MPI_INT, 0, MPI_COMM_WORLD);
  }
  else { //Scatter both A and B for form kij
    MPI_Scatter(A, (n/comm_sz)*n, MPI_INT, my_A, (n/comm_sz)*n,
        MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, (n/comm_sz)*n, MPI_INT, my_B, (n/comm_sz)*n,
        MPI_INT, 0, MPI_COMM_WORLD);
  }


  //actually solve each procs part and either gather or reduce 
  //based on form
  if(iform == 1 || iform == 2) { //not kij
    if(iform == 1) {
      Solveijk(my_A, B, my_C, n, comm_sz);
    }
    else if(iform == 2){
      Solveikj(my_A, B, my_C, n, comm_sz);
    }
    MPI_Gather(my_C, (n/comm_sz)*n, MPI_INT, C, (n/comm_sz)*n,
        MPI_INT, 0, MPI_COMM_WORLD);
  }
  else if(iform == 3) { //kij
    Solvekij(my_A, my_B, my_C, n, comm_sz);
    MPI_Reduce(my_C, C, n*n, MPI_REAL, MPI_SUM, 0, MPI_COMM_WORLD);
  }

  //BARRIER
  MPI_Barrier(MPI_COMM_WORLD);
  t_finish = MPI_Wtime();
  t_elapsed = t_finish - t_start;

  //print elapsed time
  if(my_rank == 0) {
    if(flag == "I") {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          cout << C[i*n +j] << ' ';
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << " Elapsed time = " << t_elapsed << "in seconds\n\n";
  }

  //stop MPI
  MPI_Finalize();
  return 0;
}


//function to solve form ijk
void Solveijk (int *A, int *B, int *C, int n, int comm_sz) {
  for(int i = 0; i < n/comm_sz; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < n; k++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
//function to solve form ikj
void Solveikj (int *A, int *B, int *C, int n, int comm_sz) {
  for(int i = 0; i < n; i++) {
    for(int k = 0; k< n; k++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
//function to solve form kij
void Solvekij (int *A, int *B, int *C, int n, int comm_sz) {
  for(int k = 0; k < n/comm_sz; k++) {
    for(int i = 0; i< n; i++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}







