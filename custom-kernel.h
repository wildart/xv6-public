#ifndef CUSTOM_KERNEL_INCLUDE
#define CUSTOM_KERNEL_INCLUDE

static inline void
hlt()
{
  asm volatile("hlt");
}

// atom_inc() necessary for removal of tickslock
// other atomic ops added for completeness
static inline void
atom_inc(volatile int *num)
{
  asm volatile ( "lock incl %0" : "=m" (*num));
}

static inline void
lock_inc(uint* mem)
{
  asm volatile("lock incl %0" : "=m" (mem));
}

static inline void
lock_dec(uint* mem)
{
  asm volatile("lock decl %0" : "=m" (mem));
}

static inline void
lock_add(uint* mem, uint n)
{
  asm volatile("lock add %0, %1" : "=m" (mem) : "d" (n));
}

#endif  // CUSTOM_KERNEL_INCLUDE