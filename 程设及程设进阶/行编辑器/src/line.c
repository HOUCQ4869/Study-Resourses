#include "line.h"
#include "info.h"

#include<string.h>
#define  LEN sizeof(Line)
    // TODO: 添加你所需要的其他头文件和宏定义等

void deleteLine(Line *buffer, int begin, int end) {
    int n = 0;
    Line *p1, *p2, *p3, *q;//用于储存地址来连接节点
    while(n != end){
      p2 = buffer;
      p1 = buffer->nextLine;
      if(n < begin)
        p3 = p2;
      else{
        free(buffer);
      }
      buffer = p1;
      n++;
    }
    q = buffer->nextLine;
    buffer = p3;
    buffer->nextLine = q;//连接begin前的节点与end后的节点
    // TODO: 实现该函数
}

void insertLine(Line *buffer, int line_num, const char *content) {
    Line *p, *head;//p用于开辟空间
    int n = 0;
    p = (Line *)malloc(LEN);
    while(n < line_num){
      head = buffer->nextLine;
      buffer = head;
      n++;
    }//移至第line_num行链表
    head = buffer->nextLine;
    buffer->nextLine = p;
    buffer = p;
    buffer->nextLine = head;//连接节点
    strcpy(buffer->content, content);
     // TODO: 实现该函数
}

void displayLine(Line *buffer, int begin, int end) {
    int n = 0;
    Line *p;
    while(n <= end){
      p = buffer->nextLine;
      buffer = p;
      n++;
      if(n >= begin && n <= end){
        printf("%d  %s\n", n, buffer->content);
      }
    }
    // TODO: 实现该函数
}

int readFile(Line *buffer, FILE *input) {
    int n = 0, Length = 0;
    char str[ONE_LINE_MAX_SIZE + 1];
    while(fgets(str, ONE_LINE_MAX_SIZE, input) != NULL){
      Length = strlen(str);
      *(str + Length - 1) = '\0';
      insertLine(buffer, n, str);
      n++;
    }
    return n;
    // TODO: 实现该函数 （选做）
}

void writeFile(Line *buffer, FILE *output) {
    Line *p;
    while(buffer->nextLine != NULL){
      p = buffer->nextLine;
      buffer = p;
      fputs(buffer->content, output);
      fputc('\n', output);
    }
    // TODO: 实现该函数 （选做）
}

void editLine(Line *buffer, int line_num, const char *content){
    Line *p;
    int n = 0;
    while(n != line_num){
      p = buffer->nextLine;
      buffer = p;
      n++;
    }
    strcpy(buffer->content, content);
    // TODO: 实现该函数
}
