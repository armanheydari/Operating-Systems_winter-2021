#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main (int argc,char *argv[])
{
  int pid;
  int status, a, b;
  pid = fork();
  if(pid == 0){
    cps();
    int prer = set_priority(atoi(argv[1]),atoi(argv[2]));
    printf(1, "Previous: %d\n", prer);
    cps();
  }else{
    status = waitx(&a, &b);
    printf(1, "Wait Time = %d\n Run Time = %d Total time = %d \n", a, b, status);
  }
  exit();
}
