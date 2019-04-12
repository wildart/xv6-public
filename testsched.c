#ifdef LAB4
#include "types.h"
#include "user.h"

// Must match MAXPRIO in custom.h
#define MAX_PRIORITY 7
#define CHILDREN 10

void
countForever(int i)
{
  int j, p, rc;
  unsigned long count = 0;

  j = getpid();
  p = i%MAX_PRIORITY;
  rc = setpriority(j, p);
  if (rc == 0)
    printf(1, "%d: start prio %d\n", j, p);
  else {
    printf(1, "setpriority failed. file %s at %d\n", __FILE__, __LINE__);
    exit();
  }

  while (1) {
    count++;
    if ((count & (0x1FFFFFFF)) == 0) {
      p = (p+1) % MAX_PRIORITY;
      rc = setpriority(j, p);
      if (rc == 0)
	      printf(1, "%d: new prio %d\n", j, p);
      else {
        printf(1, "setpriority failed. file %s at %d\n", __FILE__, __LINE__);
        exit();
      }
    }
  }
}

int
main(void)
{
  int i, rc;

  for (i=0; i<CHILDREN; i++) {
    rc = fork();
    if (!rc) { // child
      countForever(i);
    }
  }
  // what the heck, let's have the parent waste time as well!
  countForever(1);
  exit();
}
#endif // LAB4
