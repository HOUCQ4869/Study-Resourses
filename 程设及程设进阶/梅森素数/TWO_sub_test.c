#include <stdio.h>
struct TWO_num
{
  int length;   //储存位数
  int arr[500]; //储存二进制数
};

//实现二进制减法s1-s2
int main(void)
{
  struct TWO_num s = {0, {0}}, s1 = {5, {1, 0, 0, 0, 1}}, s2 = {4, {0, 1, 1, 1}};
  int max_length = s1.length > s2.length ? s1.length : s2.length;
  for (int i = 0; i < max_length; i++)
    s.arr[i] = s1.arr[i] - s2.arr[i];
  for (int j = 0; j < max_length; j++)
  {
    if (s.arr[j] < 0)
    {
      s.arr[j] += 2;
      s.arr[j + 1] -= 1;
    }
  }
  for(int k = max_length; k > 0; k--)
  {
    if (s.arr[max_length - 1])
      break;
    else
      max_length -= 1;
  }
  s.length = max_length;//判断结果位数
  printf("%d\n", s.length);
  for (int j = 0; j < s.length; j++)
  {
    printf("%d", s.arr[j]);
  }
  return 0;
}