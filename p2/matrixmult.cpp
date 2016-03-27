/* File matrixmulti.c
 * Name: Jon Allen
 * Class: CSCI 551
 */
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  string form;
  string flag;
  int n;

  cin >> form;
  cin >> flag;
  cin >> n;

  int A[n];
  int B[n];

  if(flag == "I") {
    for(int i = 0; i < n*n; i++) {
      cin >> A[i];
    }
    for(int i = 0; i < n*n; i++) {
      cin >> B[i];
    }
  }
  else {
  }

  if(form == "ijk") {
  }
  else if(form == "jik"){
  }
  else if(form == "ikj"){
  }
  else if(form == "jki"){
  }
  else if(form == "kij"){
  }
  else if(form == "kji"){
  }


  for(int i = 0; i < n*n; i++) {
    cout << A[i] << ' ' << B[i] << endl;
  }

  return 0;
}
