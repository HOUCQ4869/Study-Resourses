#ifndef NAVIGATION_CREAT_H
#define NAVIGATION_CREAT_H

#include "Navigation_software.h"

void CreatGraph(char *filename, ALGraph *G)
{

  // 初始化图的顶点数与弧数
  G->kind = DG;
  G->vexnum = 0;
  FILE *fp;
  // 第一次读取文件，获得图的顶点数
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("no exist\n");
    return;
  }

  while (!feof(fp))
  {
    int src, dst, dis; // 源点，目标点，距离
    fscanf(fp, "%d %d %d", &src, &dst, &dis);
    // 更新顶点数
    G->vexnum = (G->vexnum > src) ? G->vexnum : src;
    G->vexnum = (G->vexnum > dst) ? G->vexnum : dst;
  }
  fclose(fp);

  G->vertices = (VNode *)malloc((G->vexnum + 1) * sizeof(VNode));
  // 初始化图的顶点信息及相关边的信息
  for (int i = 1; i <= G->vexnum; i++)
  {
    G->vertices[i].firstarc = NULL;
  }
  // 第二次打开文件存储顶点及边的相关信息
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("no exist\n");
    return;
  }

  while (!feof(fp))
  {
    int src, dst, dis; // 源点，目标点，距离
    fscanf(fp, "%d %d %d", &src, &dst, &dis);

    // 作为第一条弧
    if (G->vertices[src].firstarc == NULL)
    {
      ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
      G->vertices[src].firstarc = p;
      p->nextarc = NULL;
      G->vertices[src].firstarc->adjvex = dst;
      G->vertices[src].firstarc->weight = dis;
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
  printf("over\n");
}

#endif