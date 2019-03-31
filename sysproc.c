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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
#ifdef USE_ATOMIC
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      return -1;
    }
    sleep(&ticks, (struct spinlock *)0);
  }
#else
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
#endif // USE_ATOMIC

  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  return uptime();
}

#ifdef CUSTOM_XV6
// Shutting down the computer
int
sys_halt(void)
{
  cprintf("Shutting down ...\n");
  outw( 0x604, 0x0 | 0x2000);
  return 0;
}
#endif // CUSTOM_XV6

#ifdef LAB1
int
sys_date(void)
{
  struct rtcdate *d;

  if(argptr(0, (void*)&d, sizeof(struct rtcdate)) < 0)
    return RETURN_FAILURE;

  cmostime(d);
  return RETURN_SUCCESS;
}
#endif // LAB1

#ifdef LAB2
uint
sys_getuid(void)
{
  return myproc()->uid;
}

uint
sys_getgid(void)
{
  return myproc()->gid;
}

uint
sys_getppid(void)
{
  struct proc *cproc = myproc();
  return cproc->parent == NULL ? cproc->pid : cproc->parent->pid;
}

int
sys_setuid(void)
{
  struct proc *cproc = myproc();
  uint newid;

  // get new id value
  if(argptr(0, (void*)&newid, sizeof(uint)) < 0)
    return RETURN_FAILURE;

  // check id value range
  if(newid < 0 || newid > 32767)
    return RETURN_FAILURE;

  // set new id
  cproc->uid = newid;

  return RETURN_SUCCESS;
}

int
sys_setgid(void)
{
  struct proc *cproc = myproc();
  uint newid;

  // get new id value
  if(argptr(0, (void*)&newid, sizeof(uint)) < 0)
    return RETURN_FAILURE;

  // check id value range
  if(newid < 0 || newid > 32767)
    return RETURN_FAILURE;

  // set new id
  cproc->gid = newid;

  return RETURN_SUCCESS;
}

int
sys_getprocs(void)
{
  return RETURN_SUCCESS;
}
#endif // LAB2
