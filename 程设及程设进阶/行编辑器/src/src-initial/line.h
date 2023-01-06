#pragma once

#include <stdio.h>

// 一行最长有 512 个字符
#define ONE_LINE_MAX_SIZE 512

// 文件名最长有 100 个字符
#define MAX_FILE_NAME 100

typedef struct _Line {
    struct _Line *nextLine; // 指向下一行，若当前行是最后一行则该项为 NULL
    char content[ONE_LINE_MAX_SIZE + 1]; // 该行的内容
} Line;

// 打印 begin 到 end 行
void displayLine(Line *buffer, int begin, int end);

// 读入文件 把当前 buffer 内容替换为文件内容
// 返回值为读入的行数
int readFile(Line *buffer, FILE *input);

// 写入文件
void writeFile(Line *buffer, FILE *output);

// 删除 [begin, end] 的行
void deleteLine(Line *buffer, int begin, int end);

// 在第 line_num 行后插入 content
void insertLine(Line *buffer, int line_num, const char *content);

// 改变第 line_num 行的内容为 content
void editLine(Line *buffer, int line_num, const char *content);

