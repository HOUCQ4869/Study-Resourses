/*
PB21111618 侯超群
*/

#include "Huffman.h"
#include "Compress.h"
#include "Extract.h"

int main(void)
{
  printf("*********Huffman编码压缩软件*********\n");
  int choose;
  while (OK)
  {
    char infilename[MAX_FILENAME], outfilename[MAX_FILENAME]; // 输入输出文件名
    printf("请输入操作:1.压缩;2.解压;3.退出;\n");
    scanf("%d", &choose);

    if (choose < 1 || choose > 3)
    {
      printf("无效输入，请重新输入;\n");
      continue;
    }
    else if (choose == 3)
    {
      printf("程序退出;\n");
      break;
    }
    else
    {
      printf("请输入待操作文件名: ");
      scanf("%s", infilename);
      printf("请输入新文件名: ");
      scanf("%s", outfilename);
      if (choose == 1)
        compress(infilename, outfilename);
      else
        extract(infilename, outfilename);
    }
  }
  return 0;
}