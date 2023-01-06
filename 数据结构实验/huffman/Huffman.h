#ifndef _HUFFMAn_H
#define _HUFFMAn_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR -1
#define MAX_FILENAME 100 // 文件名最大长度
#define MAX_NUM 9999999
// 统计字符频度的临时结点
typedef struct
{
  unsigned char str;   // 存储该节点对应字符
  unsigned int weight; // 该字符频度
} StrNode;

// 哈夫曼树结点
typedef struct
{
  unsigned char str;          // 以8bits为单元的无符号字符
  unsigned int weight;        // 每类（以二进制编码区分）字符出现频度
  char *code;                 // 字符对应的哈夫曼编码（动态分配存储空间）
  int parent, lchild, rchild; // 定义双亲和左右孩子
} HufNode, *HufTree;

// 选择最小的两个结点
void select(HufNode *huftree, unsigned int n, int *s1, int *s2)
{
  unsigned int i;
  unsigned int min = MAX_NUM; // 初始化最小值
  for (i = 0; i < n; ++i)
    if (huftree[i].parent == 0 && huftree[i].weight < min)
    {
      // 选择父节点未被标记以及权重最小的节点
      min = huftree[i].weight;
      *s1 = i;
    }
  huftree[*s1].parent = 1; // 标记该节点已有父节点
  min = MAX_NUM;           // 重新初始化便于寻找
  for (i = 0; i < n; ++i)
    if (huftree[i].parent == 0 && huftree[i].weight < min)
    {
      // 选择父节点未被标记以及权重第二小的节点
      min = huftree[i].weight;
      *s2 = i;
    }
}

// 建立赫夫曼树以及赫夫曼编码
void HuffmanCoding(HufNode *huftree, unsigned int kinds)
{
  unsigned int i;
  int s1, s2;
  for (i = kinds; i < 2 * kinds - 1; i++)
  { // 建立Huffman树
    select(huftree, i, &s1, &s2);
    // 找到最小的两个节点
    huftree[s1].parent = huftree[s2].parent = i;
    huftree[i].lchild = s1;
    huftree[i].rchild = s2;
    huftree[i].weight = huftree[s1].weight + huftree[s2].weight;
  }

  // 构建Huffman编码
  int c, f, start;
  char *cd = (char *)malloc(kinds * sizeof(char)); // 存储编码kinds种
  cd[kinds - 1] = '\0';                            // 编码结束符

  for (i = 0; i < kinds; ++i)
  { // 逐个字符求其对应的Huffman编码

    start = kinds - 1;                                                       // 编码结束符位置
    for (c = i, f = huftree[i].parent; f != 0; c = f, f = huftree[f].parent) // 从叶子到根逆向求编码
      if (huftree[f].lchild == c)
        cd[--start] = '0'; // 左子树为0
      else
        cd[--start] = '1'; // 右子树为1

    huftree[i].code = (char *)malloc((kinds - start) * sizeof(char)); // 为第i个字符编码分配存储空间
    strcpy(huftree[i].code, &cd[start]);                              // 从cd复制编码串到编码域
  }
  free(cd); // 释放工作空间
}
#endif