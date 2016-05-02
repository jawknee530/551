/* Jon Allen Assignment 3
 * CSCI 551, Judy Challinger
 * Parallel Gaussian Elimination
 * Using MTL and OpenMP
 */
#define _XOPEN_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<float.h>
#include<math.h>
#include<time.h>
#include<omp.h>

void init(double*** a, double** b, double** x, double*** M, double** B, int n);
void fill_mat(double** a, double*b, double** M, double* B, int n);
void pivot(double** a, double* b, int j, int n);
void gauss(double** a, double* b, int i, int n, int thread_count);
void gauss_row(double** a, double* b, int i, int j, int n, double t, int start
              , int thread_count);
void back_sub(double** a, double* b, double* x, int n);
double solve_iS(double** M, double* B, double* x, int n);
void set_test(double*** a, double** b, int n);
void print_mats(double*** a, double** b, int n);

int main(int argc, char* argv[])
{
  int thread_count; /* for open_mp calls */
  double start, finish; /* for timing */
  int n;      /*number of elements we're operating on */
  double** a; /* 2d array for the matrix */
  double** M; /* 2d array to back up original matrix for Ax = b */
  double* b;  /* array of answers */
  double* x;  /* array of variables we are solving for */
  double* B;  /* backup of oringal array of answers */
  double iS;  /* used to store i squared - norm value to test solution */

  if(argc != 3) {
    printf("Not the proper amount of command line arguments\n");
    return 1;
  }

  //Get thread count and n value from command line
  thread_count = strtol(argv[2], NULL, 10);
  n = strtol(argv[1], NULL, 10);

  //print amount of threads available and amount we're using
# pragma omp parallel num_threads(thread_count)
#   pragma omp master
    {
      printf("\n %d cores available \n", omp_get_num_procs());
      printf("\n %d cores being used\n\n", omp_get_num_threads());
    }

  //initialize the matrix and array memories then fill them using drand48()
  init(&a, &b, &x, &M, &B, n);
  fill_mat(a, b, M, B, n);

  //start the timer before the solution starts
  start = omp_get_wtime();

  //actual soluction: pivot, gauss, back_sub
  for(int j = 0; j < n; j++) {
    pivot(a, b, j, n);
    gauss(a, b, j, n, thread_count);
  }

  back_sub(a, b, x, n);

  //stop the timer once the solution is found
  finish = omp_get_wtime();

  //compute the iSquared-norm value to see accuracy of solution
  iS = solve_iS(M, B, x, n);

  //print iSquared-norm and the time the solution took
  printf(" I2-Norm is: %.10f\n\n", iS);
  printf(" Solution time = %.4f seconds\n\n", finish-start);
}

/*
 * Initialize the memory for matrixes a and M. arrays x, b, and B 
 */
void init(double*** a, double** b, double** x, double*** M, double** B, int n) {
  *a = malloc(n*sizeof(double*));
  *M = malloc(n*sizeof(double*));
  *b = malloc(n*sizeof(double));
  *B = malloc(n*sizeof(double));
  *x = malloc(n*sizeof(double));
  for(int i = 0; i < n; i++) {
    (*a)[i] = malloc(n*sizeof(double));
    (*M)[i] = malloc(n*sizeof(double));
    for(int j = 0; j < n; j++) {
      (*a)[i][j] = i-j;
      (*M)[i][j] = i-j;
    }
  }
  for(int i = 0; i < n; i++) {
    (*b)[i] = i;
  }
}

/*
 * Seeds the random function using time.
 * Fills the both matrixes with the same elements so M is a copy of
 * the original a.
 * Does the same thing with b and B.
 */
void fill_mat(double** a, double* b, double** M, double* B, int n) {
  srand48(time(NULL));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      a[i][j] = M[i][j] = (drand48() * 2000000 - 1000000);
    }
    b[i] = B[i] = (drand48() * 2000000 - 1000000);
  }
}

/*
 * Seaches a column for the value with the highest
 * absolute value. If the highests is not in the top
 * row then swaps it and the top in a and b.
 */
void pivot(double** a, double* b, int j, int n) {
  double max = 0;
  int cur_row = j;
  int top_row = j;
  double* tmp_row;
  double tmp_b;

  for(int i = j; i < n; i++) {
    if(fabs(a[i][j]) > fabs(max)) {
      max = a[i][j];
      top_row = i;
    }
  }
  if(cur_row != top_row) {
    tmp_b = b[j];
    tmp_row = a[j];
    a[j] = a[top_row];
    a[top_row] = tmp_row;
    b[j] = b[top_row];
    b[top_row] = tmp_b;
  }
}

/*
 * This function is where the openMP parallelizatoin occurs.
 * T is the ratio between to rows first index.
 * The calls to gauss_row are split up by row via the k variable.
 */
void gauss(double** a, double* b, int i, int n, int thread_count) {
  double t;
  int start = i;
  int k;
# pragma omp parallel for num_threads(thread_count) \
  default(none) shared(a, b, t, i, n, start, thread_count) \
  private(k)
  for(k = i+1; k < n; k++) {
    t = (a[k][i]) / (a[i][i]);
    gauss_row(a, b, k, i, n, t, start, thread_count);
  }
}

/*
 * This function will be called in parallel from gauss().
 * Each thread gets a range of rows and an index representing the
 * "starting" row from gauss().
 * Each column of a and the corresponding index of b are adjusted
 * according to the algorithm.
 */
void gauss_row(double** a, double* b, int i, int j, int n, double t, int start
    , int thread_count) {
  for(j=j; j < n; j++) {
    a[i][j] = a[i][j] - (a[start][j])*t;    
  }
    (b)[i] = (b)[i] - (b)[start]*t;
}

/*
 * Starting at the bottom row and last column we solve for Xn.
 * THe solution is subtraxed from each b index.
 * THen the next X up the line is solved and b is again adjusted.
 * Repeat until all X are found.
 */
void back_sub(double** a, double* b, double* x, int n) {
  for(int j = (n-1); j >= 0; j--) {
    x[j] = b[j] / a[j][j];
    for(int i = (n-1); i >=0; i--) {
      b[i] -= a[i][j] * x[j];
    }
  }
}

/*
 * Use the original a/M and the found array of x.
 * Dot multiply these Ax = b to solve for a new b.
 * Take the square root of the sum of the square of the differences
 * of each index of the original b and this solved for b.
 */
double solve_iS(double** M, double* B, double* x, int n) {
  double* b;
  double iS = 0;
  b = calloc(n, sizeof(double));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      b[i] += M[i][j] * x[j];
    }
  }
  
  for(int i = 0; i < n; i++) {
    iS += pow(B[i] - b[i], 2);
  }

  return sqrt(iS);
}

/*
 * EVERYTHING BELOW ARE DEBUGGING
 * TESTING FUNCTIONS
 * */

//test function to test known matrix
/*
 */
void set_test(double*** a, double** b, int n) {
  double one[3] = {25, 5, 1};
  double two[3] = {64, 8, 1};
  double three[3] = {144, 12, 1};
  double B[3] = {106.8, 177.2, 279.2};

  for(int j = 0; j < n; j++) {
    (*a)[0][j] = one[j];
  }
  for(int j = 0; j < n; j++) {
    (*a)[1][j] = two[j];
  }
  for(int j = 0; j < n; j++) {
    (*a)[2][j] = three[j];
  }
  for(int j = 0; j < n; j++) {
    (*b)[j] = B[j];
  }
}

//prints the current matrix and b
/*
 */
void print_mats(double*** a, double** b, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("%.2f ", (*a)[i][j]);
    }
    printf("%.2f ", (*b)[i]);
    printf("\n");
  }
  printf("\n");
}

