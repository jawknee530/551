/* File matrixmulti.c
 * Name: Jon Allen
 * Class: CSCI 551
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
//figure out your range
//void getRange (int &my_i, int &my_j, int &my_k, int n, int p, int my_rank);


int main(int argc, char *argv[]) {
  double t_start, t_finish, t_elapsed;
  int my_rank, comm_sz;
  string form;
  string flag;
  int n;
  int iform, ierr; //1 ijk, 2 ikj, 3 kij
  int my_i, my_j, my_k;
  int *A, *B, *C, *my_A, *my_C;
  int data[2];

  //start mpi
  MPI_Init(NULL, NULL);
  //get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //get comm size
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  if(my_rank == 0) {
    cout << "Comm_size: " << comm_sz << endl;
  }

  if(my_rank == 0) {
    form = "ijk";
    flag = "R";
    n = 4800;
    //cin >> form;
    //cin >> flag;
    //cin >> n;

    A = (int *)calloc(n*n,sizeof(int));
    B = (int *)calloc(n*n,sizeof(int));
    C = (int *)calloc(n*n,sizeof(int));
    my_A = (int *)calloc((n/comm_sz)*n,sizeof(int));
    if(form != "kij") {
      my_C = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }
    else {
      my_C = (int *)calloc(n*n,sizeof(int));
    }

    for(int i = 0; i < n*n; i++) {
      C[i] = 0;
    }

    if(flag == "I") {
      for(int i = 0; i < n*n; i++) {
        //cin >> A[i];
      }
      for(int i = 0; i < n*n; i++) {
        //cin >> B[i];
      }
    }
    else if(flag == "R") {
      srand(time(NULL));
      for(int i = 0; i < n*n; i++) {
        A[i] = rand() % 100;
      }
      for(int i = 0; i < n*n; i++) {
        B[i] = rand() % 100;
      }
    }
    if(form == "ijk") {
      iform = 1;
    }
    else if(form == "ikj"){
      iform = 2;
    }
    else if(form == "kij"){
      iform = 3;
    }
    //debug printing
    for(int i = 0; i < n*n; i++) {
      //cout << A[i] << ' ';
    }
    //cout << endl;
    for(int i = 0; i < n*n; i++) {
      //cout << B[i] << ' ';
    }
    //cout << endl;

    data[0] = n;
    data[1] = iform;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  t_start = MPI_Wtime();

  MPI_Bcast(&data, 2, MPI_INT, 0, MPI_COMM_WORLD);

  if(my_rank != 0) {
    n = data[0];
    B = (int *)calloc(n*n,sizeof(int));
    my_A = (int *)calloc((n/comm_sz)*n,sizeof(int));
    iform = data[1];
    if(iform != 3) {
      my_C = (int *)calloc((n/comm_sz)*n,sizeof(int));
    }
    else {
      my_C = (int *)calloc(n*n,sizeof(int));
    }
  }

  //Broadcast and scatter B & A
  MPI_Bcast(B, n*n, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Scatter(A, (n/comm_sz)*n, MPI_INT, my_A, (n/comm_sz)*n,
      MPI_INT, 0, MPI_COMM_WORLD);

  //debug printing
  //cout << my_rank <<" n: "<< data[0] <<" form: "<< data[1] << endl;
  //cout << my_rank <<" B: ";
  for(int i = 0; i < n*n; i++){
    //cout << B[i] << ' ';
  }
  //cout << endl;
  //cout << my_rank <<" my_A: ";
  for(int i = 0; i < (n/comm_sz)*n; i++){
    //cout << my_A[i] << ' ';
  }
  //cout << endl;

  //compute your spots for C
  if(iform == 1 || iform == 2) {
    if(iform == 1) {
      Solveijk(my_A, B, my_C, n, comm_sz);
    }
    else if(iform == 2){
      Solveikj(my_A, B, my_C, n, comm_sz);
    }
    MPI_Gather(my_C, (n/comm_sz)*n, MPI_INT, C, (n/comm_sz)*n,
        MPI_INT, 0, MPI_COMM_WORLD);
  }
  else if(iform == 3) {
    Solvekij(my_A, B, my_C, n, comm_sz);
    MPI_Reduce(my_C, C, n*n, MPI_REAL, MPI_SUM, 0, MPI_COMM_WORLD);
  }

  //BARRIER
  MPI_Barrier(MPI_COMM_WORLD);
  t_finish = MPI_Wtime();
  t_elapsed = t_finish - t_start;

  //prints my_C
  if(iform == 1 || iform == 2) {
    //cout << my_rank <<" my_C: ";
    for(int i = 0; i < (n/comm_sz)*n; i++){
      //cout << my_C[i] << ' ';
    }
    //cout << endl;
  }
  else {
    //cout << my_rank <<" my_C: ";
    for(int i = 0; i < n*n; i++){
      //cout << my_C[i] << ' ';
    }
    //cout << endl;
  }

  //BARRIER
  MPI_Barrier(MPI_COMM_WORLD);

  //print C
  if(my_rank == 0) {
    //cout << endl;
    //cout << my_rank <<" C: ";
    for(int i = 0; i < n*n; i++){
      //cout << C[i] << ' ';
    }
    //cout << endl;
  }

  if(my_rank == 0) {
    cout << "Elapsed time = " << t_elapsed << "in seconds\n";
  }

  //stop MPI
  MPI_Finalize();
  return 0;
}


void Solveijk (int *A, int *B, int *C, int n, int comm_sz) {
  for(int i = 0; i < n/comm_sz; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < n; k++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solveikj (int *A, int *B, int *C, int n, int comm_sz) {
  for(int i = 0; i < n; i++) {
    for(int k = 0; k< n; k++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solvekij (int *A, int *B, int *C, int n, int comm_sz) {
  for(int k = 0; k < n/comm_sz; k++) {
    for(int i = 0; i< n; i++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}







