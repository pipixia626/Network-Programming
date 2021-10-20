#include<stdio.h>
#include<unistd.h>

int main(){
   char* av[]={"ls","-l",NULL};
   execv("/bin/ls",av);
   perror("execv failed");
   return 0;
}