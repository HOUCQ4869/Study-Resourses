#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "Navigation_software.h"

// dijkstra算法

// 寻找未标记节点中距出发点最近的节点
int Find(int *mark, int *dis, ALGraph *G)
{
  int k = 0;
  while (mark[k] != 0)
    k++;
  for (int i = 0; i < G->vexnum; i++)
  {
    if (mark[i] == 0 && dis[k] > dis[i])
      k = i;
  }
  return k;
}

// 更新距离
void UpdateDis(int src, int *dis, int *mark, int *path, ALGraph *G)
{
  int n = 0;
  int k = src; // 从源点开始寻找最近的未标记节点
  dis[k] = 0;
  while ((n++) <= G->vexnum)
  {
    for (int i = 0; i < G->vexnum; i++)
    {
      // 对于未标记节点
      if (!mark[i])
      {
        // 更新最短距离以及前驱结点
        if (dis[i] > dis[k] + GetDis(G, k, i))
        {
          dis[i] = dis[k] + GetDis(G, k, i);
          path[i] = k;
        }
      }
    }
    //
    k = Find(mark, dis, G);
    mark[k] = 1; // 标记该节点
  }
}

// 根据目标点以及前驱结点输出路径
void OutPrint(int src, int dst, int *dis, int *path, ALGraph *G)
{
  int k, n = 0;
  int *l; // 输出路径
  l = (int *)malloc(G->vexnum * sizeof(int));
  l[0] = dst; // 从目标点开始记录
  k = dst;
  // 向前回溯
  while (k != src)
  {
    l[n++] = path[k];
    k = path[k];
  }
  printf("最短路径为:");
  for (int i = n - 1; i >= 0; i--)
  {
    if (i == n - 1)
      printf("%d", l[i]);
    else
      printf("->%d", l[i]);
  }
  printf("\n");
  printf("最短路径长度为:%d\n", dis[dst]);
}

// 迪杰斯特拉算法实现最短路径的求解
void dijkstra(char *filename)
{
  // 读取文件建立相关有向图
  ALGraph *G = (ALGraph *)malloc(sizeof(ALGraph));
  CreatGraph(filename, G);

  int *dis, *path, *mark;
  mark = (int *)malloc((G->vexnum) * sizeof(int)); // 标记各点是否被访问
  dis = (int *)malloc((G->vexnum) * sizeof(int));  // 记录各点到源点的最短距离
  path = (int *)malloc((G->vexnum) * sizeof(int)); // 记录最短路径的前驱结点

  // 源点，目标点，结束标志
  int src, dst, choose = 1;
  while (choose)
  {
    // 初始化记录数组
    for (int i = 0; i < G->vexnum; i++)
    {
      mark[i] = 0;
      dis[i] = MAX_DIS;
      path[i] = -1;
    }
    printf("源点:");
    scanf("%d", &src);
    printf("目标点:");
    scanf("%d", &dst);

    UpdateDis(src, dis, mark, path, G);
    OutPrint(src, dst, dis, path, G);
    printf("\n");
    printf("请输入1确认继续操作,否则输入0终止程序:");
    scanf("%d", &choose);
  }

  // 释放内存
  for (int i = 0; i < G->vexnum; i++)
  {
    ArcNode *p = G->vertices[i].firstarc, *q = NULL;
    if (p != NULL)
      q = p->nextarc;
    while (q)
    {
      free(p);
      p = q;
      q = q->nextarc;
    }
    free(p);
  }
  free(G);
  free(dis);
  free(path);
  free(mark);
}

#endif