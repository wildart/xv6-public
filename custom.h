#ifndef CUSTOM_INCLUDE
#define CUSTOM_INCLUDE

#define TRUE 1
#define FALSE 0
#define RETURN_SUCCESS 0
#define RETURN_FAILURE -1

#define NUL 0
#ifndef NULL
#define NULL NUL
#endif  // NULL

#define TPS 100   // ticks-per-second
#define SCHED_INTERVAL (TPS/10)  // see trap.c

int atoo(const char*);
char* itoa(int, char*);
char* ftoa(float, char*, uint);

#endif  // CUSTOM_INCLUDE
