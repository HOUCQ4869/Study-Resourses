#include <stdio.h>
int main(void)
{
  int x = 7;
  int str[200] = {1, 0}, n = 199;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < 200; j++)
    {
      str[j] *= 2;
    } //先相乘记录结果
    for (int m = 0; m < 200; m++)
    {
      str[m + 1] += str[m] / 10;
      str[m] %= 10;
    } //再实现依次进位
  }
  str[0] -= 1;
  while (str[n] == 0)
  {
    n--;
  } //找到第一个非0数
  for (int i = n; i >= 0; i--)
    printf("%d", str[i]);
  printf("\n");
  return 0;
}