#include <stdio.h>
struct TWO_num
{
  int length;   //储存位数
  int arr[500]; //储存二进制数
};

//实现二进制平方
int main(void)
{
  struct TWO_num s1 = {4, {0, 0, 1, 1}};
  struct TWO_num s = {s1.length * 2 - 1, {0}};
  for (int i = 0; i < s.length; i++)
  {
    for (int j = 0; j < s1.length && i - j >= 0; j++)
    {
      if (s1.arr[i - j] == 0)
        continue;
      s.arr[i] += s1.arr[j];
    }
  }
  for(int k = 0; k < s.length + 1; k++)
  {
    if(s.arr[k] > 1)
    {
      s.arr[k + 1] += s.arr[k] / 2;
      s.arr[k] %= 2;
    }
  }
  if(s.arr[s.length])
    s.length = s.length + 1;
  printf("%d\n", s.length);
  for (int j = 0; j < s.length; j++)
  {
    printf("%d", s.arr[j]);
  }
  return 0;
}