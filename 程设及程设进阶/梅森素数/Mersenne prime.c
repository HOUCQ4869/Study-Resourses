#include <stdio.h>
#include <math.h>

//具有长度的二进制数组结构体表示
struct TWO_num
{
  int length;    //储存位数
  int arr[2000]; //储存二进制数
};

//实现第x个梅森素数到二进制数组的转换
struct TWO_num change(int x)
{
  struct TWO_num s = {0, {0}}; //定义新结构体用于储存第x个梅森素数
  s.length = x;
  for (int i = 0; i < x; i++)
    s.arr[i] = 1;
  return s;
}

//实现判断两个等位数组二进制数大小
int comp(int *s1, int *s2, int length)
{
  for (int i = 0; i < length; i++)
  {
    if (s1[i] < s2[i])
      return 1; //若s1小于s2返回值为1
    else if (s1[i] > s2[i])
      return 0; //若s1大于s2返回值为0
  }
  return 2; //若s1等于s2返回值为2
}

//实现二进制加法
struct TWO_num add(struct TWO_num s1, struct TWO_num s2)
{
  struct TWO_num s = {0, {0}};                                    //定义结构体储存计算结果并用于返回值
  int max_length = s1.length > s2.length ? s1.length : s2.length; // max_length为两个大整数中的最大位数
  for (int i = 0; i < max_length + 1; i++)
  {
    if (s1.arr[i] + s2.arr[i] + s.arr[i] > 1)
    {
      s.arr[i] = s1.arr[i] + s2.arr[i] + s.arr[i] - 2;
      s.arr[i + 1] = 1;
    } //若和大于1需要进位
    else
      s.arr[i] = s1.arr[i] + s2.arr[i] + s.arr[i];
  }
  if (s.arr[max_length]) //判断结构体中数组的第max_length+1为是否有值
    s.length = max_length + 1;
  else
    s.length = max_length; //至多max_length+1位
  return s;
}

//实现二进制减法s1-s2
struct TWO_num sub(struct TWO_num s1, struct TWO_num s2)
{
  struct TWO_num s = {0, {0}};                                    //定义结构体储存计算结果并用于返回值
  int max_length = s1.length > s2.length ? s1.length : s2.length; // max_length为两个大整数中的最大位数
  for (int i = 0; i < max_length; i++)
    s.arr[i] = s1.arr[i] - s2.arr[i];
  for (int j = 0; j < max_length; j++)
  {
    if (s.arr[j] < 0) //如果差小于0则需要借位
    {
      s.arr[j] += 2;
      s.arr[j + 1] -= 1;
    }
  }
  for (int k = max_length; k > 0; k--) //从后往前判断第一个0所处的位置
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
  struct TWO_num s = {s1.length * 2 - 1, {0}}; //定义结构体储存计算结果并用于返回值
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

//实现二进制取模(模s2.arr[])
struct TWO_num mod(struct TWO_num s1, struct TWO_num s2)
{
  struct TWO_num s0 = {0, {0}};        //定义结构体储存计算结果并用于返回值
  int det = s1.length - s2.length - 1; //用于记录两个二进制数的位数差
  while (det >= 0)
  {
    struct TWO_num s = {0, {0}}; //初始化结构体
    for (int i = 0; i < s2.length; i++)
      s.arr[det + i] = s2.arr[i];
    for (int j = 0; j < det; j++)
      s.arr[j] = 0; //首先使模乘二达到s1.length-1位数
    s.length = s1.length - 1;
    s1 = sub(s1, s);
    det = s1.length - s2.length - 1;
  } //循环减去模的倍数直至位数差小于0
  if (s1.length < s2.length)
    return s1; //若s1位数小于s2则其为余数
  else if (comp(s1.arr, s2.arr, s1.length) == 2)
    return s0;
  else
    return comp(s1.arr, s2.arr, s1.length) ? s1 : s2; //若位数相同则调用comp函数
}

//实现特定数列求二进值制
struct TWO_num L(struct TWO_num s_)
{
  struct TWO_num s0 = {2, {0, 1}}; //初始化结构体
  s_ = mult(s_);
  s_ = sub(s_, s0);
  return s_;
}

//判断是否是素数
int
prime(int x)
{
  int i;
  for (i = 2; i <= sqrt(x); i++)
  {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

//将梅森素数判定的二进制数转化为十进制即2^x-1并打印
void change_Prin(int x)
{
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
}

int main(void)
{
  struct TWO_num s = {0, {0}};      //定义结构体并初始化
  printf("2 3\n");                  //由于2^2-1为素数可先打印以便减少后续循环次数
  for (int i = 3; i < 1000; i += 2) //排除二的倍数
  {
    if (prime(i))
    {
      struct TWO_num s_ = {3, {0, 0, 1}}; //每次初始化结构体
      s = change(i);
      for (int j = 0; j < i - 2; j++)
      {
        s_ = L(s_);
        s_ = mod(s_, s);
      } //实现卢卡斯莱默检验法
      if (s_.length == 0)
      {
        printf("%d ", i);
        change_Prin(s.length);
      }
    }
  }
  return 0;
}