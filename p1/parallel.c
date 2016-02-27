#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

long double Get_y(long double x);

int Update_progress(long double n, long double i, int eq_count);

long double Compute_error(long double approx);

long double Find_area(long double a, long double b, long double n, double h);

char progress[11] = {'-','-','-','-','-','-','-','-','-','-','\0'};
long double true_value = 4003.7209001513268265;
long double absolute_relative_error;

int main( int argc, char *argv[] ) {
  int my_rank, comm_sz;
  double local_n, local_a, loacal_b;
  double a, b, n, h;
  double local_sum, total_sum;
  char t_val[23] = {'4', '.', '0', '0', '3', '7', '2', '0', 
                    '9', '0', '0', '1', '5', '1', '3', '2', 
                    '6', '8', '2', '6', '5', '9', '\0'};

  //Compute the accepting error
  long double accepting_error = 0.5*pow(10, -14);

  //start MPI
  MPI_Init(NULL, NULL);
  //get my process rank
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //get comm size
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  //process 0 assigns variables from command line input
  if (my_rank == 0) {
    printf("Enter a, b, and n\n");
    scanf("%f %f %f", &a, &b, &n);
    printf("--------------------------------------------------------------\n");
    printf("[----------]\n");
    for(int i = 1; i < comm_sz; i++) {
      MPI_Send(&a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      MPI_Send(&b, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      MPI_Send(&n, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(&a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&n, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  //start timer
  clock_t start = clock(), diff;

  h = (b - a)/n;
  local_n = n/comm_sz;

  local_sum = Find_area(local_a, local_b, local_n, h);
  //end time
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;

  //printf("[==========]\n\n");

  //printf("Numbers must match to this point--V\n");
  //printf("True_Value is ----[ %se+03\n", t_val);
  //printf("Current Guess is -[ %.20Le\n\n", result);
  //printf("Accepting Error -------[ %.15Le\n", accepting_error);
  //printf("Relative True Error ---[ %.15Le\n\n", relative_true_error);
  //printf("Time taken: %d minutes, %d seconds, and %d milliseconds\n\n", 
  //       (msec/1000)/60, (msec/1000)%60, msec%1000);

  //if(relative_true_error < accepting_error) {
  //  printf("Realtive True Error is less than the Accepting Error! Success!\n");
  //  printf("--------------------------------------------------------------\n");
  //}

  return 0;
}

long double Find_area(long double a, long double b, long double n, double h) {
  //h is the width of each slice
  //Compute the y value at points a and b then halve them because
  //those two slices are only used once each
  long double y = Get_y(a)/2 + Get_y(b)/2;
  //int eq_count = 0;

  //Loop that adds up all of the n slices of the function
  for (long double i = 1; i <= n-1; i++) {
    //eq_count = Update_progress(n, i, eq_count);
    y += Get_y(a+i*h);
  }

  //find the are by multiplying the sum of the slices by
  //the slice of each width and get the relative truee error
  long double result = y*h;
  return result;
}

//compute the y value of any given x based on given function
long double Get_y(long double x){
  return cos(x/3)-2*cos(x/5)+5*sin(x/4)+8;
}

long double Compute_error(long double approx) {
  long double true_error = true_value - approx;
  return fabs(true_error/true_value);
}


int Update_progress(long double n, long double i, int eq_count) {
  double ratio = i/n;
  //printf("%f", ratio);
  if (.09 < ratio && ratio < .11 && eq_count < 1) {
    progress[0] = '=';
    eq_count += 1;
    printf("[%s]\n", progress);
  }
  else if (.19 < ratio && ratio < .21 && eq_count < 2) {
    progress[1] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.29 < ratio && ratio < .31 && eq_count < 3) {
    progress[2] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.39 < ratio && ratio < .41 && eq_count < 4) {
    progress[3] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.49 < ratio && ratio < .51 && eq_count < 5) {
    progress[4] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.59 < ratio && ratio < .61 && eq_count < 6) {
    progress[5] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.69 < ratio && ratio < .71 && eq_count < 7) {
    progress[6] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.79 < ratio && ratio < .82 && eq_count < 8) {
    progress[7] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  else if (.89 < ratio && ratio < .92 && eq_count < 9) {
    progress[8] = '=';
    printf("[%s]\n", progress);
    eq_count += 1;
  }
  return eq_count;
}
















