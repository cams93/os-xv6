#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int fin, initial, resta;
  initial=uptime();
  
  if(fork()==0)
  {
    exec(argv[1],&argv[1]);
  }

  wait();
  fin=uptime();
  resta = fin-initial;
  printf(1,"El tiempo es: %d \n", resta);
  exit();
  return 0;
}
