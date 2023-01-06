/*
先在四个数中任选两个数进行运算，得到三个数
后再在这三个数中任选两个数进行运算，得到两个数
最后进行最后两个数的运算，得到可能的结果。
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int sum = 0;      //用于判断有解
char str[20];     //用于储存输出的表达式
char temp_str[4]; //临时储存数字

//递归程序实现判断
void Search(int n, double *arr)
{
  int i, j, k;
  double new_arr[4]; //用于传递到下一层递归程序
  if (n == 1)
  {
    //考虑除法计算结果为小数，如果精度差小于1e-6则满足
    if (fabs(arr[0] - 24) <= 1e-6)
    {
      printf("True!\n");
      puts(str);
      sum++;
      exit(0);
    }
  }
  for (i = 0; i < n - 1; i++)
  {
    if (n == 4) //初始元素
    {
      if (arr[i] > 9)
      {
        str[0] = (int)arr[i] / 10 + 48;
        str[1] = (int)arr[i] % 10 + 48;
        str[2] = '\0';
      }
      else
      {
        str[0] = (int)arr[i] + 48;
        str[1] = '\0';
      }
    }
    char temp3_str[20];
    strcpy(temp3_str, str);     //记录厡字符便于返回
    for (j = i + 1; j < n; j++) //循环两次选择两个数进行运算
    {
      char temp2_str[20];
      strcpy(temp2_str, str); //记录厡字符便于返回
      for (k = 0; k < 6; k++) //进行四则运算
      {
        char temp1_str[20];
        strcpy(temp1_str, str); //记录厡字符便于返回
        char temp0_str[20];
        if (arr[j] > 9)
        {
          temp_str[0] = (int)arr[j] / 10 + 48;
          temp_str[1] = (int)arr[j] % 10 + 48;
          temp_str[2] = '\0';
        }
        else
        {
          temp_str[0] = (int)arr[j] + 48;
          temp_str[1] = '\0';
        } //临时储存添加元素
        switch (k)
        {
        case 0:
          new_arr[0] = arr[i] + arr[j];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, str);
          strcpy(str, temp0_str); //字符数组前加'('
          strcat(str, "+");
          strcat(str, temp_str);
          strcat(str, ")"); //同时进行字符串的赋值
          break;
        case 1:
          new_arr[0] = arr[i] * arr[j];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, str);
          strcpy(str, temp0_str); //字符数组前加'('
          strcat(str, "*");
          strcat(str, temp_str);
          strcat(str, ")");
          break;
        case 2:
          new_arr[0] = arr[i] - arr[j];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, str);
          strcpy(str, temp0_str); //字符数组前加'('
          strcat(str, "-");
          strcat(str, temp_str);
          strcat(str, ")");
          break;
        case 3:
          new_arr[0] = arr[j] - arr[i];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, temp_str);
          strcpy(temp_str, temp0_str); //字符数组前加'('
          strcat(temp_str, "-");
          strcat(temp_str, str);
          strcpy(str, temp_str);
          strcat(str, ")");
          break;
        case 4:
          new_arr[0] = arr[i] / arr[j];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, str);
          strcpy(str, temp0_str); //字符数组前加'('
          strcat(str, "/");
          strcat(str, temp_str);
          strcat(str, ")");
          break;
        case 5:
          new_arr[0] = arr[j] / arr[i];
          temp0_str[0] = '(';
          temp0_str[1] = '\0';
          strcat(temp0_str, temp_str);
          strcpy(temp_str, temp0_str); //字符数组前加'('
          strcat(temp_str, "/");
          strcat(temp_str, str);
          strcpy(str, temp_str);
          strcat(str, ")");
          break;
        }

        for (int s = 0, m = 1; s < n; s++)
        {
          if (s == j || s == i)
            continue;
          new_arr[m++] = arr[s];
        }                       //将运算结果储存到新数组的前n-1位
        Search(n - 1, new_arr); //再次递归
        strcpy(str, temp1_str); //恢复字符串
      }
      strcpy(str, temp2_str); //恢复字符串
    }
    strcpy(str, temp3_str); //恢复字符串
  }
}

int main(void)
{
  double arr[4]; //储存四个整数
  scanf("%lf %lf %lf %lf", &arr[0], &arr[1], &arr[2], &arr[3]);
  Search(4, arr);
  if (sum == 0)
    printf("False!"); //判断是否无解
  return 0;
}