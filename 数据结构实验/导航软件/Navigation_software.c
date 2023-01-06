/*
PB21111618 侯超群
*/

#include "Navigation_software.h"
#include "Dijkstra.h"

int main()
{
  char filename[100];
  printf("请输入txt文档名:");
  scanf("%s", filename);
  dijkstra(filename);
  printf("结束运行");
  return 0;
}