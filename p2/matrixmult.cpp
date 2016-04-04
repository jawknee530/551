/* File matrixmulti.c
 * Name: Jon Allen
 * Class: CSCI 551
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
using namespace std;

void Solveijk (int *A, int *B, int *C, int n);
void Solvejik (int *A, int *B, int *C, int n);
void Solveikj (int *A, int *B, int *C, int n);
void Solvejki (int *A, int *B, int *C, int n);
void Solvekij (int *A, int *B, int *C, int n);
void Solvekji (int *A, int *B, int *C, int n);
//figure out your range
void getRange (int &my_i, int &my_j, int &my_k, int n, int p, int my_rank);


int main(int argc, char *argv[]) {
  int my_rank, comm_sz;
  string form;
  string flag;
  int n;
  int my_i, my_j, my_k;

  //start mpi
  MPI_Init(NULL, NULL);
  //get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //get comm size
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  if(my_rank == 0) {
    cin >> form;
    cin >> flag;
    cin >> n;

    int A[n*n];
    int B[n*n];
    int C[n*n];

    for(int i = 0; i < n*n; i++) {
      C[i] = 0;
    }

    if(flag == "I") {
      for(int i = 0; i < n*n; i++) {
        cin >> A[i];
      }
      for(int i = 0; i < n*n; i++) {
        cin >> B[i];
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
  }

  //set each procs i, j, k
  getRange(my_i, my_j, my_k, n, comm_sz);

  if(form == "ijk") {
    Solveijk(A, B, C, n);
  }
  else if(form == "jik"){
    Solvejik(A, B, C, n);
  }
  else if(form == "ikj"){
    Solveikj(A, B, C, n);
  }
  else if(form == "jki"){
    Solvejki(A, B, C, n);
  }
  else if(form == "kij"){
    Solvekij(A, B, C, n);
  }
  else if(form == "kji"){
    Solvekji(A, B, C, n);
  }
  


  for(int i = 0; i < n*n; i++) {
    cout << A[i] << ' ';
  }
  cout << endl;
  for(int i = 0; i < n*n; i++) {
    cout << B[i] << ' ';
  }
  cout << endl;
  for(int i = 0; i < n*n; i++) {
    cout << C[i] << ' ';
  }
  cout << endl;

  //stop MPI
  MPI_Finalize();
  return 0;
}

void getRange (int &my_i, int &my_j, int &my_k, int n, int p, int my_rank) {
  if(p < n) {
    my_i = my_rank * (n/p) % n;
    my_j = n;
    my_k = n;
  }
  else if(n <= p < (n*n)) {
    my_i = my_rank/n;
    my_j = my_rank * ((n*n)/p) % n;
    my_k = n;
  }
  else if((n*n) <= p < (n*n*n)) {
    my_i = my_rank / (n*n);
    my_j = my_rank / n;
    my_k = my_rank * ((n*n*n)/p) % n;
  }
}

void Solveijk (int *A, int *B, int *C, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < n; k++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solvejik (int *A, int *B, int *C, int n) {
  for(int j = 0; j < n; j++) {
    for(int i = 0; i< n; i++) {
      for(int k = 0; k < n; k++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solveikj (int *A, int *B, int *C, int n) {
  for(int i = 0; i < n; i++) {
    for(int k = 0; k< n; k++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solvejki (int *A, int *B, int *C, int n) {
  for(int j = 0; j < n; j++) {
    for(int k = 0; k< n; k++) {
      for(int i = 0; i < n; i++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solvekij (int *A, int *B, int *C, int n) {
  for(int k = 0; k < n; k++) {
    for(int i = 0; i< n; i++) {
      for(int j = 0; j < n; j++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}
void Solvekji (int *A, int *B, int *C, int n) {
  for(int k = 0; k < n; k++) {
    for(int j = 0; j< n; j++) {
      for(int i = 0; i < n; i++) {
        C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
      }
    }
  }
}







