#include <stdio.h>

struct TWO_num
{
  int length;   //储存位数
  int arr[500]; //储存二进制数
};

int main(void)
{
  struct TWO_num s1 = {3, {1, 1, 1}}, s2 = {5, {1, 0, 0, 1, 1}}; /*左侧低位右侧高位*/
  struct TWO_num s = {0, {0}};
  int max_length = s1.length > s2.length ? s1.length : s2.length;
  for (int i = 0; i < max_length + 1; i++)
  {
    if (s1.arr[i] + s2.arr[i] + s.arr[i] > 1)
    {
      s.arr[i] = s1.arr[i] + s2.arr[i] + s.arr[i] - 2;
      s.arr[i + 1] = 1;
    }
    else
      s.arr[i] = s1.arr[i] + s2.arr[i] + s.arr[i];
  }
  if (s.arr[max_length])
    s.length = max_length + 1;
  else
    s.length = max_length;
  printf("%d\n", s.length);
  for (int j = 0; j < s.length; j++)
  {
    printf("%d", s.arr[j]);
  }
  return 0;
}
//倒序输入倒序输出