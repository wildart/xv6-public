#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define SHOW_LINES 10

char buf[128];

void
head(int fd, int l)
{
    int i, n, c;

    c = n = 0;
    while(l > 0 && (n = read(fd, buf, sizeof(buf))) > 0){
        for(i=0; i<n; i++){
            if(buf[i] == '\n'){
                write(1, buf+c, i-c+1); // write line to stdout
                c = i+1;   // change a pivot to point on a first character in a line
                l--;       // count written lines
                if (l == 0)
                    break; // stop looking for new line symbol
            }
        }
        if(c != n && l > 0){ // some characters left in the buffer
            write(1, buf+c, n-c); // show them on a screen
        }
        c = 0;
    }
    if(n < 0){
        printf(1, "head: read error\n");
        exit();
    }
}

int
main(int argc, char *argv[])
{
  int fd, i, l;
  l = SHOW_LINES; // set default number of shown lines

  if(argc <= 1){
    head(0, SHOW_LINES);
  } else {
    i = 1; // parameter index set to point to the first parameter

    if (argc > 2) { // check if there is more then 1 parameter
        char *tmp = argv[i];
        l = atoi((char *)(tmp+1));
        if(l <= 0){ // check if parameter was parsed correctly
            l = SHOW_LINES;
        }
        i++; // go to next parameter
    }
    if((fd = open(argv[i], O_RDONLY)) < 0){
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, l);
    close(fd);
  }
  exit();
}
