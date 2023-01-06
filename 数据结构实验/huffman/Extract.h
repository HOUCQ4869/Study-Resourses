#ifndef _EXTRACT_H
#define _EXTRACT_H

#include "Huffman.h"

// 解压函数
void extract(char *infilename, char *outfilename)
{
  HufTree huftree; // 解压时待构建的赫夫曼树

  unsigned int file_length; // 文件长度
  unsigned int kinds;       // 存储字符种类
  unsigned char str;        // 临时字符

  FILE *infile, *outfile;
  unsigned int i;
  // 判断输入文件是否存在
  if ((infile = fopen(infilename, "rb")) == NULL)
  {
    printf("文件不存在;\n");
    return;
  }
  // 读取文件长度
  fread(&file_length, sizeof(unsigned int), 1, infile);
  // 读取字符种类数
  fread(&kinds, sizeof(unsigned int), 1, infile);

  huftree = (HufNode *)malloc((2 * kinds - 1) * sizeof(HufNode)); // 分配赫夫曼树节点空间
  // 逐个读取字符，权重
  for (i = 0; i < kinds; i++)
  {
    fread(&huftree[i].str, sizeof(unsigned char), 1, infile);   // 读入字符
    fread(&huftree[i].weight, sizeof(unsigned int), 1, infile); // 读入字符对应权重
    huftree[i].parent = 0;
  }
  // 初始化后面结点的parent
  for (; i < 2 * kinds - 1; ++i)
    huftree[i].parent = 0;

  HuffmanCoding(huftree, kinds); // 建立赫夫曼树

  outfile = fopen(outfilename, "wb");
  unsigned int cur;    // 用于匹配字符对应节点
  cur = 2 * kinds - 2; // 从根节点开始寻找
  while (file_length != 0)
  {
    // 每次读取8bit,用临时字符str储存
    fread(&str, sizeof(unsigned char), 1, infile);

    for (i = 0; i < 8; ++i)
    {
      // 由根向下直至叶节点匹配编码对应字符
      if (str & 0b10000000) // 判断最高位1或0
        cur = huftree[cur].rchild;
      else
        cur = huftree[cur].lchild;

      // 到达叶子结点，即可翻译字符写入
      if (cur < kinds)
      {
        fwrite(&huftree[cur].str, sizeof(unsigned char), 1, outfile);

        if ((--file_length) == 0)
          break;             // 当文件写入完时跳出
        cur = 2 * kinds - 2; // 重新从根节点开始寻找
      }
      str <<= 1; // 左移，寻找下一节点
    }
  }
  // 关闭文件
  fclose(infile);
  fclose(outfile);

  // 释放内存
  free(huftree);

  printf("解压成功;\n");
} // extract()

#endif