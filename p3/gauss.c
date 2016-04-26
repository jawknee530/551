#include<stdlib.h>
#include<stdio.h>
#include<float.h>
#include<math.h>

void init(double*** a, double** b, double** x, int n);
void set_test(double*** a, double** b, int n);
void print_mats(double*** a, double** b, int n);
void pivot(double*** a, double* b, int j, int n);
void gauss(double*** a, double* b, int i, int n);
void back_sub(double*** a, double** b, double** x, int n);
void gauss_row(double*** a, double* b, int i, int j, int n, double t, int start);
void table_init(int **t, int n);
void table_fill(int *t, int n);
void table_print(int *t, int n);

int main()
{
  int n = 3;
  double** a;
  double *b;
  double *x;
  double *M;
  double *B;
  int *table;

  init(&a, &b, &x, n);
  set_test(&a, &b, n);
  print_mats(&a, &b, n);
  table_init(&table, n);
  table_fill(table, n);
  //table_print(table, n);

  for(int j = 0; j < n; j++) {
    pivot(&a, b, j, n);
    gauss(&a, b, j, n);
    print_mats(&a, &b, n);
  }

  back_sub(&a, &b, &x, n);

  printf("Solution: \n");
  for(int i = 0; i < n; i++) {
    printf("%.2f ", x[i]);
  }
  printf("\n");
}

//solves back substitution
void back_sub(double*** a, double** b, double** x, int n) {
  for(int j = (n-1); j >= 0; j--) {
    (*x)[j] = (*b)[j] / (*a)[j][j];
    for(int i = (n-1); i >=0; i--) {
      (*b)[i] -= (*a)[i][j] * (*x)[j];
    }
  }
}


//prints the current matrix and b
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

//Initialize A and B in memory
void init(double*** a, double** b, double** x, int n) {
  *a = malloc(n*sizeof(double*));
  *b = malloc(n*sizeof(double));
  *x = malloc(n*sizeof(double));
  for(int i = 0; i < n; i++) {
    (*a)[i] = malloc(n*sizeof(double));
    for(int j = 0; j < n; j++) {
      (*a)[i][j] = i-j;
    }
  }
  for(int i = 0; i < n; i++) {
    (*b)[i] = i;
  }
}

//test function to test known matrix
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


//PIVOT function to swap rows based on absolute value
void pivot(double*** a, double* b, int j, int n) {
  double max = 0;
  int cur_row = j;
  int top_row = j;
  double* tmp_row;
  double tmp_b;

  for(int i = j; i < n; i++) {
    if(fabs((*a)[i][j]) > fabs(max)) {
      max = (*a)[i][j];
      top_row = i;
    }
  }
  if(cur_row != top_row) {
    tmp_b = b[j];
    tmp_row = (*a)[j];
    (*a)[j] = (*a)[top_row];
    (*a)[top_row] = tmp_row;
    b[j] = b[top_row];
    b[top_row] = tmp_b;
  }
}

void gauss(double*** a, double* b, int i, int n) {
  double t;
  int start = i;
  for(int k = i+1; k < n; k++) {
    t = ((*a)[k][i]) / ((*a)[i][i]);
    gauss_row(a, b, k, i, n, t, start);
  }
}

void gauss_row(double*** a, double* b, int i, int j, int n, double t, int start) {
  for(j; j < n; j++) {
    (*a)[i][j] = (*a)[i][j] - ((*a)[start][j])*t;    
  }
    (b)[i] = (b)[i] - (b)[start]*t;
}

/*EVERYTHING BELOW ARE DEBUGGING
 * TESTING FUNCTIONS
 * */

void table_init(int **t, int n) {
  *t = malloc(n*sizeof(int));
}

void table_fill(int *t, int n) {
  for(int i = 0; i < n; i++) {
    t[i] = i;
  }
}

void table_print(int *t, int n) {
  for(int i = 0; i < n; i++) {
    printf("%d ", t[i]);
  }
  printf("\n");
}
