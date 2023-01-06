#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//以文本文件形式储存N皇后的解
void fprint(int n, int *arr)
{
  FILE *fp;
  int i, j;
  if ((fp = fopen("N_queen_solve.txt", "w+")) == NULL) //以txt文件储存N皇后解
  {
    printf("File cannot open! ");
    exit(0);
  }
  fprintf(fp, "%d\n", n); //将皇后个数存入文件方便读取检验
  for (i = 1; i <= n; i++)
  {
    for (j = 1; j <= n; j++)
    {
      if (arr[i] == j)
        fprintf(fp, "Q"); // Q代表皇后
      else
        fprintf(fp, "#");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
  fclose(fp);
}

//检验第i行第j列上是否可以摆放皇后
int judg(int i, int j, int *arr)
{
  for (int k = 1; k < i; k++)
  {
    //如果位于同一列，或处于斜线位置上，则不能摆放
    if (arr[k] == j || abs(k - i) == abs(arr[k] - j))
      return 0;
  }
  return 1;
}

//放置皇后到棋盘上
void n_queens(int i, int n, int *arr)
{
  int j;
  if (i > n) //当行数满足所求时即可输出解法
  {
    fprint(n, arr);
    exit(1); //正常退出程序
  }
  else //不满足时继续判断下一行
  {
    for (j = 1; j <= n; j++)
    {
      if (judg(i, j, arr)) //判断第i行第j列是否满足
      {
        arr[i] = j;
        n_queens(i + 1, n, arr); //保证第i行满足后，用递归调用该函数继续判断下一行的满足列
      }
    }
  }
}

int main()
{
  int n;
  int *arr; //用于储存皇后在每一行的位置
  printf("请输入皇后个数：");
  scanf("%d", &n);
  //对数组进行动态内存分配
  if ((arr = (int *)malloc(sizeof(int) * (n + 1))) == NULL)
    return -1;
  //对数组进行初始化
  for (int i = 1; i <= n; i++)
    arr[i] = 0;
  n_queens(1, n, arr);
  free(arr); //释放内存
  return 0;
}
