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

int checkPassword(char *user, char *password, char *directory)
{
    int i, pos, fd;
    char line[200];
    char userFile[25];
    char passwordFile[25];
    fd = openFile("users");
    i = readLine(fd,line);
    
    while( i > 0){
        pos = 0;
        pos = parse(line,':',userFile,pos);
        pos = parse(line,':',passwordFile,pos);
        pos = parse(line,':',directory,pos);
        if(strcmp(userFile,user)==0 && strcmp(passwordFile,password)==0)
        {
            printf(1,"logged on \n");
            close(fd);
            return 0;
        }
        i = readLine(fd,line);
    }
  printf(1,"username or password is incorrect \n");
  close(fd);
  return 1;
}


int main(int argc, char *argv[]){
    char user[25];
    char password[25];
    char directory[200];
    while(1){
        printf(1, "\nUser: ");
        gets(user, 25);
        user[strlen(user)-1]='\0';
        printf(1, "Password: ");
        gets(password, 25);
        password[strlen(password)-1]='\0';
        if(checkPassword(user, password, directory) == 0)
        {
            break;
        }
    }
    char *argv1[] = {directory, 0};
    
    printf(1, "init: starting sh\n");
    if(fork() == 0){
        exec("sh", argv1);
        printf(1, "init: exec sh failed \n");
        exit();
    }
    wait();
    exit();
}