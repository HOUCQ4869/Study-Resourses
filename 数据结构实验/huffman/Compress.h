#ifndef _COMPRESS_H
#define _COMPRESS_H

#include "Huffman.h"

/*
对于二进制文件的压缩，将文件的相关信息储存于压缩后文件的前列，以文件长度，字符种类，各字符与其对应的权重，最后是正式翻译后的二进制文件
*/
// 压缩函数
void compress(char *infilename, char *outfilename)
{
  unsigned int i, j;
  unsigned int kinds;           // 字符种类
  unsigned char str;            // 用于储存每次读入及写入的字符
  unsigned int file_length = 0; // 文件长度
  FILE *infile, *outfile;       // 输入输出文件指针
  StrNode node_temp;            // 暂存节点
  HufTree huftree;              // 构建的赫夫曼树

  StrNode *str_nodes = (StrNode *)malloc(256 * sizeof(StrNode)); // 用于储存各字符以及相关权重

  //  初始化用于储存字符的节点
  for (i = 0; i < 256; ++i)
  {
    str_nodes[i].weight = 0;
    str_nodes[i].str = (unsigned char)i; // 下标对应ASCLL码中字符
  }

  // 第一次打开待压缩文件根据字符频度用于建立赫夫曼树
  if ((infile = fopen(infilename, "rb")) == NULL)
  {
    printf("文件不存在;\n");
    return;
  }
  // 记录字符频度
  fread(&str, sizeof(unsigned char), 1, infile); // 读入一个字符
  while (!feof(infile))
  {

    str_nodes[str].weight++;                       // 读取的字符对应权重加一
    file_length++;                                 // 文件长度加一
    fread(&str, sizeof(unsigned char), 1, infile); // 读入一个字符
  }
  fclose(infile);

  // 排序，根据已读取的字符频度按权重排序
  for (i = 0; i < 256 - 1; ++i)
    for (j = i + 1; j < 256; ++j)
      if (str_nodes[i].weight < str_nodes[j].weight)
      {
        node_temp = str_nodes[i];
        str_nodes[i] = str_nodes[j];
        str_nodes[j] = node_temp;
      }

  // 计算字符种类数
  for (kinds = 0; kinds < 256; ++kinds)
    if (str_nodes[kinds].weight == 0)
      break;

  huftree = (HufNode *)malloc((2 * kinds - 1) * sizeof(HufNode));

  // 初始化前kinds个结点
  for (i = 0; i < kinds; ++i)
  {
    huftree[i].str = str_nodes[i].str;
    huftree[i].weight = str_nodes[i].weight;
    huftree[i].parent = 0;
  }
  free(str_nodes);

  // 初始化后后面结点
  for (; i < 2 * kinds - 1; ++i)
    huftree[i].parent = 0;

  // 创建赫夫曼树并生成赫夫曼编码
  HuffmanCoding(huftree, kinds);

  // 打开待写入文件，写入文件长度，字符种类数，所有字符以及对应权重，翻译后字符编码
  outfile = fopen(outfilename, "wb");
  // 首先写入文件长度
  fwrite(&file_length, sizeof(unsigned int), 1, outfile); // 写入文件长度
  // 接着写入字符种类数
  fwrite(&kinds, sizeof(unsigned int), 1, outfile);
  for (i = 0; i < kinds; ++i)
  {
    // 依次写入字符以及对应权重，各kinds个
    fwrite(&huftree[i].str, sizeof(unsigned char), 1, outfile);
    fwrite(&huftree[i].weight, sizeof(unsigned int), 1, outfile);
  }

  // 第二次打开待压缩文件，根据已编排的赫夫曼编码翻译并写入待写入文件
  infile = fopen(infilename, "rb");              // 以二进制形式打开待压缩的文件
  fread(&str, sizeof(unsigned char), 1, infile); // 每次读取8bits

  // 初始化暂存编码区域
  char code_temp[256]; // 临时存储编码，待8位时以字节输出
  for (i = 0; i < 256; i++)
    code_temp[i] = '\0';

  while (!feof(infile))
  {
    // 根据已编排的赫夫曼编码匹配字符对应编码
    for (i = 0; i < kinds; ++i)
      if (str == huftree[i].str)
        strcat(code_temp, huftree[i].code);

    // 当翻译后的编码累计至8位，以字符对应写入outfile，否则继续读取储存到code_temp中
    while (strlen(code_temp) >= 8)
    {
      str = '\0';
      for (i = 0; i < 8; ++i)
      {
        str <<= 1;
        if (code_temp[i] == '1')
          str |= 1;
      }
      fwrite(&str, sizeof(unsigned char), 1, outfile); // 将字节对应编码存入文件
      strcpy(code_temp, code_temp + 8);                // 编码缓存去除已处理的前八位
    }
    fread(&str, sizeof(unsigned char), 1, infile); // 继续读取
  }
  // 最后不足8位编码时
  unsigned int code_length; // 赫夫曼编码长度
  code_length = strlen(code_temp);
  // 根据长度，不足位补零存入
  if (code_length > 0)
  {
    str = '\0';
    for (i = 0; i < code_length; ++i)
    {
      str <<= 1;
      if (code_temp[i] == '1')
        str |= 1;
    }
    str <<= 8 - code_length;
    fwrite(&str, sizeof(unsigned char), 1, outfile);
  }

  // 关闭文件
  fclose(infile);
  fclose(outfile);

  // 释放内存
  for (i = 0; i < kinds; ++i)
    free(huftree[i].code);
  free(huftree);

  printf("压缩成功;\n");
} // compress

#endif