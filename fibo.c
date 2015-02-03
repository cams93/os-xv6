#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])  // argc - numero de elementos que recibo argv - arreglo va atener los valores que se les esta pasando
{
  int n=20,c,next,first=0,second=1;
	int slp = 65535;
	int prio = 0;

	switch(argc){
	case 3:
		prio = atoi(argv[2]);
    setpriority(prio);
	case 2:
		n = atoi(argv[1]);
		break;
	}


  printf(1, "Prio %d Term %d of Fibonacci series is : ",prio,n);

  for ( c = 0 ; c < n ; c++ ){
  	if ( c <= 1 )
  		next = c;
  	else{
  		next = first + second;
  		first = second;
  		second = next;
    }
    //Busy for awhile
    while(slp){slp--;};
    slp = 65535;
   }
  printf(1,"%d \n",next);
  exit();
}