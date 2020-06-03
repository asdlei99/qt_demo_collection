/** This program contains some examples of memory 
    leaks and other bad programming practices. */
#include <iostream>

int badpointer2(int k) {
  int* ip = new int[3];
  ip[0] = k;
  return ip[3];   /* out of bounds index */
}  /* memory leak */


int main() {
  using namespace std;
  int* iptr;
  int num(4), k;  /* k is uninitialized */
  /* what is the state of iptr? */
  cout << iptr[num-1] << endl; 
  cout << badpointer2(k) << endl;
}

