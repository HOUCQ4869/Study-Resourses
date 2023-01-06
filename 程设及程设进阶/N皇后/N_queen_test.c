#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//测试arr[]数组储存的解是否满足
int test(int *arr, int n)
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = i + 1; j <= n; j++)
    {
      if ((arr[i] == arr[j]) || (fabs(arr[j] - arr[i]) == j - i))
        return 0;
    }
  }
  return 1;
}

int main(void)
{
  FILE *fp;
  int i, j, n; // n为皇后个数
  int *arr;    //一维数组储存N皇后的解
  char *str;   //用于储存每一行的字符，并不断更新

  if ((fp = fopen("N_queen_solve.txt", "r+")) == NULL)
  {
    printf("File cannot open! ");
    exit(0);
  }
  fscanf(fp, "%d", &n); //读取皇后个数

  //进行动态内存分配
  if ((arr = (int *)malloc(sizeof(int) * (n + 1))) == NULL)
    return -1;
  if ((str = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
    return -1;

  //从文件中读取皇后的位置，并储存在一维数组中
  for (i = 0; i < n; i++)
    for (j = 0; j <= n; j++) //多一个换行符
    {
      fscanf(fp, "%c", &str[j]);
      if (str[j] == 'Q')
        arr[i + 1] = j; //刚开始吞掉换行符故为第j个
    }
  fclose(fp);

  if (test(arr, n))
    printf("TRUE");
  else
    printf("ERROR");
    
  free(arr); //释放内存

  return 0;
}