#include<stdlib.h>
#include<stdio.h>

void init(int*** a, int n);
void table_init(int **t, int n);
void table_fill(int *t, int n);
void table_print(int *t, int n);

int main()
{
  int n = 4;
  int** a;
  int *table;

  init(&a, n);
  table_init(&table, n);
  table_fill(table, n);
  table_print(table, n);


  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      //printf("%d ", a[i][j]);
    }
    //printf("\n");
  }
}

void init(int*** a, int n) {
  *a = malloc(n*sizeof(int*));
  for(int i = 0; i < n; i++) {
    (*a)[i] = malloc(n*sizeof(int));
    for(int j = 0; j < n; j++) {
      (*a)[i][j] = j;
    }
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
