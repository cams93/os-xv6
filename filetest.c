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


int main(int argc, char *argv[]){
  int fd, i,pos;
  char line[200];
  char name[100];
  char password[100];
  char directory[100];
  char *fileName = argv[1];
  char *user = argv[2];
  char *pass = argv[3];
  int found=0;
  fd = openFile(fileName);
  i = readLine(fd,line);
  while( i > 0){
    pos = 0;
    pos = parse(line,':',name,pos);
    pos = parse(line,':',password,pos);
    pos = parse(line,':',directory,pos);
    if(strcmp(name,user)==0 && strcmp(password,pass)==0)
    {
        found=1;
        printf(1,"sesion iniciada \n");
        printf(1,"tu directorio es: %s\n",directory);
        //dir=strcpy(dir, directory);
    }
    //printf(1,"name: %s\n",name);
    //printf(1,"password: %s\n",password);
    i = readLine(fd,line);
    
  }
  if(found==0){
    printf(1,"usuario o password incorrectos \n");
  }
  close(fd);
  exit();
}