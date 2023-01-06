#include <stdio.h>
#include <math.h>
int main(void)
{
  int i, x = 17;
  for (i = 2; i <= sqrt(x); i++)
  {
    if (x % i == 0)
    {
      printf("%d\n", 0);
      return 0;
    }
  }
  printf("%d\n", 1);
  return 0;
}
