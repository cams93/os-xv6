// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 }; //cahr*argv[2][100]   

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("login", argv);  //ejecutar login cuando termine solo modificar sh -> login
      printf(1, "init: exec sh failed\n");
      //exit();
    }
    wait();
    while((wpid=wait()) >= 0 && wpid != pid) //ocupamos esto
      printf(1, "zombie!\n");  //break para que termine este e init crea otro login
  }
}
