#ifndef _NAVIGATION_SOFTWARE_H
#define _NAVIGATION_SOFTWARE_H

#include <stdio.h>
#include <stdlib.h>

// 图的相关数据结构
#define MAX_DIS 9999999 // 图中最大距离

typedef enum
{
  DG,
  DN,
  UDG,
  UDN
} GraphKind; // 图的类型

typedef struct ArcNode
{
  int adjvex;              // 该弧所指向的顶点的位置
  struct ArcNode *nextarc; // 指向下一条弧的指针
  int weight;              // 该段弧的权重
} ArcNode;

typedef struct VNode
{
  ArcNode *firstarc; // 指向第一条依附该顶点的弧的指针
} VNode, *AdjList;

typedef struct
{
  AdjList vertices;
  int vexnum;     // 图的当前顶点数
  GraphKind kind; // 图的种类标志
} ALGraph;

// 创建有向图
void CreatGraph(char *filename, ALGraph *G)
{

  // 初始化图的类型与顶点数
  G->kind = DG;
  G->vexnum = 0;
  FILE *fp;
  // 第一次读取文件，获得图的顶点数
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("no exist\n");
    return;
  }
  printf("开始更新顶点数\n");
  while (!feof(fp))
  {
    int src, dst, dis; // 源点，目标点，距离
    fscanf(fp, "%d %d %d", &src, &dst, &dis);
    // 更新顶点数
    G->vexnum = (G->vexnum > src) ? G->vexnum : src;
    G->vexnum = (G->vexnum > dst) ? G->vexnum : dst;
  }
  G->vexnum++; // 考虑0
  fclose(fp);
  printf("已更新顶点共%d个\n", G->vexnum + 1);
  G->vertices = (VNode *)malloc(G->vexnum * sizeof(VNode));
  // 初始化图的顶点信息及相关边的信息
  for (int i = 0; i < G->vexnum; i++)
  {
    G->vertices[i].firstarc = NULL;
  }
  // 第二次打开文件存储顶点及边的相关信息
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("文件不存在\n");
    return;
  }
  printf("开始读取相关信息\n");
  while (!feof(fp))
  {
    int src, dst, dis; // 源点，目标点，距离
    fscanf(fp, "%d %d %d", &src, &dst, &dis);
    //  作为第一条弧
    if (G->vertices[src].firstarc == NULL)
    {
      ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
      G->vertices[src].firstarc = p;
      p->nextarc = NULL;
      p->adjvex = dst;
      p->weight = dis;
    } // 向后查找为空的下一条
    else
    {
      ArcNode *p = G->vertices[src].firstarc;
      while (p->nextarc)
        p = p->nextarc;
      ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
      p->nextarc = q;
      q->nextarc = NULL;
      q->adjvex = dst;
      q->weight = dis;
    }
  }
  fclose(fp);
  printf("读取结束\n");
}

// 得到邻接表中源点src到目标点dst的距离
int GetDis(ALGraph *G, int src, int dst)
{
  int dis = MAX_DIS;
  ArcNode *p = G->vertices[src].firstarc;
  while (p)
  {
    if (p->adjvex == dst)
    {
      dis = p->weight;
      break;
    }
    else
      p = p->nextarc;
  }
  return dis;
}

#endif