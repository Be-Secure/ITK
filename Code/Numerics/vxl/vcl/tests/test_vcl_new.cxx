/*
  fsm@robots.ox.ac.uk
*/
#include <vcl_new.h>

struct X 
{
  double *p;
  X() { p = new double[37]; }
  ~X() { delete [] p; }
};

int main() 
{
  X my_x;
  
  vcl_destroy(&my_x);
  new (&my_x) X; // vcl_construct(&my_x);

  return 0;
}
