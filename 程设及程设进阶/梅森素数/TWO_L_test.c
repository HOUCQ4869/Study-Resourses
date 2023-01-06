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

//实现二进制平方
struct TWO_num mult(struct TWO_num s1)
{
  struct TWO_num s = {s1.length * 2 - 1, {0}};
  for (int i = 0; i < s.length; i++)
  {
    for (int j = 0; j < s1.length && i - j >= 0; j++)
    {
      if (s1.arr[i - j] == 0)
        continue;
      s.arr[i] += s1.arr[j];
    }
  } //先各位直接相加
  for (int k = 0; k < s.length + 1; k++)
  {
    if (s.arr[k] > 1)
    {
      s.arr[k + 1] += s.arr[k] / 2;
      s.arr[k] %= 2;
    }
  } //再转化为二进制
  if (s.arr[s.length])
    s.length = s.length + 1; //至多s.length+1位，只需判断首位是否为1
  return s;
}
int main(void)
{
  struct TWO_num s_ = {4, {0, 1, 1, 1}}, s0 = {2, {0, 1}};
  s_ = mult(s_);
  s_ = sub(s_, s0);
  prin(s_);
  return 0;
}