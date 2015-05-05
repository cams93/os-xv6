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

int parse(char *line,char del,char *word,int pos){
  int i = pos;
  int j = 0;
  while(line[i] != del && line[i] != '\n' && line[i] != '\0' )
    word[j++] = line[i++];
  word[j] = '\0';
  return i+1;
}

void strcat ( char *s , char *t){
  int i , j;
  for( i=0;s[i] !='\0'; i++)
    ;
   for( j=0; t[j] !='\0';j++)
     s[i+j]=t[j];
 
   s[i+j]='\0';
}

int main(int argc, char *argv[]){
  if(argc != 3){
    printf(2, "Usage: add username password \n");
    exit();
  }
  int fd, fk, i, pos;
  int exist = 0;
  char line[200];
  char name[100];
  char *user = argv[1];
  char *pass = argv[2];
  fd = openFile("/users");
  fk = openFile("tmp");
  i = readLine(fd,line);
  while( i > 0){
    pos = 0;
    pos = parse(line,':',name,pos);
    if(strcmp(name,user)==0)
    {
        write(fk, user, strlen(user));
        write(fk, ":", 1);
        write(fk, pass, strlen(pass));
        if(strcmp(name,"root")==0)
        {
            write(fk, ":/", 2);
        }
        else
        {
            write(fk, ":/home/", 7);
            write(fk, user, strlen(user));
        }
        write(fk,"\n", 1);
        exist = 1;
        printf(1,"password changed \n");
    }
    else
    {
        write(fk, line, strlen(line));
    }
    i = readLine(fd,line);
  }
  readLine(fd,line);
  close(fd);
  close(fk);
  if(exist == 0)
  {
    printf(1,"the user must exist to change its password \n");
  }
  else
  {
    unlink("/users");
    move("tmp","/users");
  }
  
  exit();
}