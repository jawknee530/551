#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long double Get_y(long double x);

int Update_progress(long double n, long double i, int eq_count);

long double Compute_error(long double approx);

long double Find_area(long double a, long double b, long double n);

char progress[11] = {'-','-','-','-','-','-','-','-','-','-','\0'};
long double absolute_relative_error;

int main( int argc, char *argv[] ) {
  long double a=100;
  long double b=600;
  int start_n=10;
  int n;
  long double accepting_error = 0.5*pow(10, -14);
  int best_n;
  int lowest_n = 1;
  long double best_err = 1;
  long double lowest_err = 1;
  long double result;
  
  //start the timer after getting input
  clock_t start = clock(), diff;

  for(int i = 1; i<1000; i++) {
    n = 10395000 + start_n*i;
    result = Find_area(a, b, n);
    if(absolute_relative_error < accepting_error && 
       absolute_relative_error < best_err) {
          best_n = n;
          best_err = absolute_relative_error;
          if(lowest_n == 1) {
            lowest_n = n;
            lowest_err = best_err;
      }
    }
  }

  //end time
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;

  printf("[--------------------------------------------------------------]\n");
  printf("The Result is   : %.15Le\n"
         "Best Error is   : %.15Le\n"
         "With N value of : %d\n", result, best_err, best_n);
  printf(">------------------------------------------------------------<\n");
  printf("Lowest Error is   : %.15Le\n"
         "With N value of   : %d\n", lowest_err, lowest_n);
         printf("Time taken: %d minutes, %d seconds, and %d milliseconds\n\n", 
                (msec/1000)/60, (msec/1000)%60, msec%1000);
  printf("[--------------------------------------------------------------]\n");
  //printf("[----------]\n");



  //printf("[==========]\n\n");

  //printf("Numbers must match to this point--V\n");
  //printf("True_Value is ----[ %se+03\n", t_val);
  //printf("Current Guess is -[ %.20Le\n\n", result);
  //printf("Accepting Error -------[ %.15Le\n", accepting_error);
  //printf("Relative True Error ---[ %.15Le\n\n", relative_true_error);
  //printf("Time taken: %d minutes, %d seconds, and %d milliseconds\n\n", 
  //       (msec/1000)/60, (msec/1000)%60, msec%1000);

  //if(relative_true_error < accepting_error) {
  //printf("Realtive True Error is less than the Accepting Error! Success!\n");
  //printf("--------------------------------------------------------------\n");
  //}

  return 0;
}

long double Find_area(long double a, long double b, long double n) {
  //h is the width of each slice
  //Compute the y value at points a and b then halve them because
  //those two slices are only used once each
  long double h = (b-a)/n;
  long double y = Get_y(a)/2 + Get_y(b)/2;
  int eq_count = 0;

  //Loop that adds up all of the n slices of the function
  for (long double i = 1; i <= n-1; i++) {
    //eq_count = Update_progress(n, i, eq_count);
    y += Get_y(a+i*h);
  }

  //find the are by multiplying the sum of the slices by
  //the slice of each width and get the relative truee error
  long double result = y*h;
  absolute_relative_error = Compute_error(result);
  return result;
}

//compute the y value of any given x based on given function
long double Get_y(long double x){
  return cos(x/3)-2*cos(x/5)+5*sin(x/4)+8;
}

long double Compute_error(long double approx) {
  long double true_value = 4003.7209001513268265;
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
















