#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int openFile(char *fileName){
  int fd;
  if((fd = open(fileName, O_CREATE|O_RDWR)) < 0){ //O_CREATE|O_RDWR||O_RDONLY |O_WRONLY
    printf(1, "filetest: cannot open %s\n", fileName);
    exit();
  }
  return fd;
}

int readLine(int fd,char *line){
  int i = 0,n=0;
  char c;
  n = read(fd, &c, 1);
  while( (n > 0) && (c != '\n') ){
    line[i++] = c;
    n = read(fd, &c, 1);
  }
  line[i++] = '\n';
  line[i] = '\0';
  return i-1;
}

int main(int argc, char *argv[]){
  int fd, i;
  char line[200];
  char *user = argv[1];
  char *pass = argv[2];
  fd = openFile("users");
  i = readLine(fd,line);
  while( i > 0){
    i = readLine(fd,line);
  }
  readLine(fd,line);
  write(fd,"\n", 1);
  write(fd, user, strlen(user));
  write(fd, ":", 1);
  write(fd, pass, strlen(pass));
  write(fd, ":/home/", 7);
  write(fd, user, strlen(user));
  printf(1,"user added: \n");
  close(fd);
  exit();
}