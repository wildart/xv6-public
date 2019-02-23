#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[128];

void
head(int fd)
{
  int i, n, c, l;

  c = 0;
  l = 10;
  while((n = read(fd, buf, sizeof(buf))) > 0 && l > 0){
    for(i=0; i<n; i++){
      if(buf[i] == '\n')
      {
        write(1, buf+c, i-c+1); // write line to stdout
        l--; // count written lines
        c = i+1;
        if (l == 0)
          break; // stop looking for new line symbol
      }
    }
  }
  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    head(0);
  }
  else
  {
    i = 1;
    if((fd = open(argv[i], O_RDONLY)) < 0){
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd);
    close(fd);
  }
  exit();
}
