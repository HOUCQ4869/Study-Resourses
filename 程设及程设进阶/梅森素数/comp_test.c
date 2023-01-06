#include <stdio.h>

//具有长度的二进制数组结构体表示
struct TWO_num
{
  int length;    //储存位数
  int arr[2000]; //储存二进制数
};

int main(void)
{
  struct TWO_num s1 = {3, {1, 0, 1}}, s2 = {3, {1, 1, 1}};
  int length = s1.length;
  for (int i = 0; i < length; i++)
  {
    if (s1.arr[i] < s2.arr[i])
    {
      printf("%d\n", 1); //若s1小于s2返回值为1
      return 0;
    }
    else if (s1.arr[i] > s2.arr[i])
    {
      printf("%d\n", 0); //若s1大于s2返回值为0
      return 0;
    }
  }
  printf("%d\n", 2); //若s1等于s2返回值为2
  return 0;
}