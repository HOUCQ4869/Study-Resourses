#pragma once
#include "line.h"

typedef struct {
    Line *buffer; // 各行组成的链表
    int currentLine; // 当前所在行
    int totalLine; // 一共有多少行
} Editor;


// 分发各指令, 根据输入命令的不同来调用不同的处理函数
void dispatchCmd(Editor *editor, const char *cmd);

// 执行删除指令，删除 [begin, end] 的行
void cmdDelete(Editor *editor, int begin, int end);

// 执行展示指令，打印 [begin, end] 的行
void cmdDisplay(Editor *editor, int begin, int end);

// 执行插入指令
void cmdInsert(Editor *editor);

// 执行添加指令
void cmdAppend(Editor *editor);

// 读入 filename 文件
void cmdRead(Editor *editor, const char *filename);

// 写入 filename 文件
void cmdWrite(Editor *editor, const char *filename);

// 改变当前所在行
void cmdChangeLine(Editor *editor, int new_line);

// 重新输入当前行的内容，之前的内容清空
void cmdReinput(Editor *editor);

// 打印用法
void usage(void);

// 启动编辑器
void run(Editor *editor);

// 错误处理
void error(const char *format, ...);
