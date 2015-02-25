#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//to halt
int sys_halt (void)
{
  outw(0xB004, 0x0|0x2000);
  return 0;
}

//to reboot
int sys_reboot (void)
{
  outb(0x64, 0xfe);
  return 0;
}

//set priority
int sys_setpriority (void)
{
  int priority;
  argint(0,&priority); //& pasarle la direccion
  proc->priority = priority; //proc esta la estructura proc
  return 0;
  //argint leer el registro donde el usuario esta pasano los parametros
}

//regresa el PID del padre del proceso 
int
sys_getppid(void)
{
  return proc -> parent -> pid;
}

//pone en la posicion especifica en el proceso de la se;al vector
int
sys_signal(void)
{
  int signum;
  sighandler_t * handler;
  if(argint(0,&signum)<0)
    return -1;
  if(argptr(1,(void*) &handler, sizeof(&handler)) < 0)
    return -1;
  signum-=1;
  proc -> signals[signum] = handler;
  return signum+1;
} 

