#include "types.h"
#include "stat.h"
#include "user.h"

#ifdef LAB0
int
main(int argc, char *argv[])
{
    printf(1, "Hello World (uptime %d)\n", uptime());
    exit();
}
#endif // LAB0