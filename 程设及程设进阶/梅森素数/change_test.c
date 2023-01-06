#include <stdio.h>

//具有长度的二进制数组结构体表示
struct TWO_num
{
  int length;    //储存位数
  int arr[2000]; //储存二进制数
};

int main(void)
{
  int x = 5;
  struct TWO_num s = {0, {0}}; //定义新结构体用于储存第x个梅森素数
  s.length = x;
  for (int i = 0; i < x; i++)
    s.arr[i] = 1;
  for(int j = 0; j < x; j++)
    printf("%d", s.arr[j]);
  return 0;
}