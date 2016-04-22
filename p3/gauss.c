#include<stdlib.h>
#include<stdio.h>
#include<float.h>

void init(double*** a, double** b, int n);
void pivot(double*** a, double* b, int j, int n);
void gauss(double*** a, double* b, int i, int n);
void table_init(int **t, int n);
void table_fill(int *t, int n);
void table_print(int *t, int n);

int main()
{
  int n = 4;
  double** a;
  double *b;
  int *table;

  init(&a, &b, n);
  table_init(&table, n);
  table_fill(table, n);
  //table_print(table, n);

  for(int j = 0; j < n; j++) {
    pivot(&a, b, j, n);
    gauss(&a, b, j, n);
  }


  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("%.2f ", a[i][j]);
    }
    printf("\n");
  }
  for(int i = 0; i < n; i++) {
    printf("%.2f ", b[i]);
    printf("\n");
  }
}

void init(double*** a, double** b, int n) {
  *a = malloc(n*sizeof(double*));
  *b = malloc(n*sizeof(double));
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

void pivot(double*** a, double* b, int j, int n) {
  double max = -DBL_MAX;
  int cur_row = j;
  int top_row = j;
  double* tmp_row;
  double tmp_b;

  for(int i = j; i < n; i++) {
    if((*a)[i][j] > max) {
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
  for(int k = i; k < n; k++) {

  }
}

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
