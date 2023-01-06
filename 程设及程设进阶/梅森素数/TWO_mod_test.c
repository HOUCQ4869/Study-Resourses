#include <stdio.h>

struct TWO_num
{
  int length;   //储存位数
  int arr[500]; //储存二进制数
};

//实现打印结构体
void prin(struct TWO_num s)
{
  printf("%d\n", s.length);
  for (int i = 0; i < s.length; i++)
    printf("%d", s.arr[i]);
  printf("\n");
}

//实现判断两个等位数组二进制数大小
int comp(int *s1, int *s2, int length)
{
  for (int i = 0; i < length; i++)
  {
    if (s1[i] < s2[i])
      return 1;
    else if(s1[i] > s2[i])
      return 0;
  }
  return 2;
}

//实现二进制减法s1-s2
struct TWO_num sub(struct TWO_num s1, struct TWO_num s2)
{
  struct TWO_num s = {0, {0}};
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
  for (int k = max_length; k > 0; k--)
  {
    if (s.arr[max_length - 1])
      break;
    else
      max_length -= 1;
  }
  s.length = max_length; //判断结果位数
  return s;
}
int main(void)
{
  struct TWO_num s1 = {8, {0, 1, 0, 0, 0, 0, 1, 1}}, s2 = {5, {1, 1, 1, 1, 1}};
  struct TWO_num s0 = {0, {0}};
  int det = s1.length - s2.length - 1; //两个二进制数的位数差
  while (det >= 0)
  {
    struct TWO_num s = {0, {0}};
    for (int i = 0; i < s2.length; i++)
      s.arr[det + i] = s2.arr[i];
    for (int j = 0; j < det; j++)
      s.arr[j] = 0;
    s.length = s1.length - 1;
    s1 = sub(s1, s);
    det = s1.length - s2.length - 1;
  }
  if (s1.length < s2.length)
    prin(s1);
  else if(comp(s1.arr, s2.arr, s1.length) == 2)
    prin(s0);
  else
    prin(comp(s1.arr, s2.arr, s1.length) ? s1 : s2);

  return 0;
}
