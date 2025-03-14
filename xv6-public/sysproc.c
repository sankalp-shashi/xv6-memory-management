#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
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
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_numvp(void)
{
  struct proc *p = myproc(); // Get the current process
  int num_pages;

  // Calculate the number of pages up to the program size
  num_pages = PGROUNDUP(p->sz) / PGSIZE;

  // Add 1 for the stack guard page
   num_pages += 1;

  return num_pages;
}

int sys_numpp()
{
  struct proc *p = myproc(); // Get the current process
  pde_t *pgdir = p->pgdir;   // Page directory of the current process
  uint va;                   // Virtual address
  int num_pages = 0;

  // Iterate over each virtual page in the user part of the address space

  for (va = 0; va < p->sz; va += PGSIZE)
  {
    pte_t *pte = walkpgdir(pgdir, (void *)va, 0); // Get the PTE for the virtual address
    if (pte && (*pte & PTE_P))
    {
      num_pages++; // Count the page if it's present
    }
  }

  // Add 1 to include the stack guard page
   num_pages += 1;
  return num_pages;
}

int
sys_mmap(void) {
     int size;
    struct proc *curproc = myproc();

    // Validate input
    if (argint(0, &size) < 0 || size <= 0 || size % PGSIZE != 0 || curproc->sz + size > KERNBASE) {
        return -1; // Invalid input
    }

    // Ensure alignment of curproc->sz
    uint start_addr = PGROUNDUP(curproc->sz);
    curproc->sz = start_addr + size; // Expand virtual address space

    return start_addr; // Return starting address of new memory region
}
