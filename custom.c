#include "types.h"
#include "defs.h"

int
atoo(const char *s)
{
  int n, sign;

  n = 0;
  while (*s == ' ') s++;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+'  || *s == '-')
    s++;
  while('0' <= *s && *s <= '7')
    n = n*8 + *s++ - '0';
  return sign*n;
}

char*
itoa(int n, char *s)
{
  int i, j, sign;
  char c;

  if ((sign = n) < 0)
    n = -n;

  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';

  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }

  return s;
}

char*
ftoa(float n, char *s, uint len)
{
  int d;
  uint pos, sz;
  char curr[1];

  d = (int)n;
  itoa(d, s);

  if (n < 0) {
    n *= -1;
    d *= -1;
  }

  sz = strlen(s);
  pos = sz;
  s[pos++] = '.';

  while(pos < (sz + len)){
    n = n - (float)d;  // hack off the whole part of the number
    n *= 10;  // move next digit over
    d = (int)n;  // get next digit
    itoa(d, curr); // convert digit to string
    s[pos++] = *curr; // add digit to result string and increment pointer
  }
  return s;
}
