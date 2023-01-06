#include "editor.h"
#include "line.h"
#include "info.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#define is_same(input, expect) (strcmp(input, expect) == 0)

// TODO: 添加你需要的头文件以及宏定义等


void run(Editor *editor) {
    // TODO: 正确的给 editor 赋初值
    char cmd[MAX_FILE_NAME + 16];
    while (true) {
        printf("cmd> ");
        gets(cmd);
        dispatchCmd(editor, cmd);
    }
}

void dispatchCmd(Editor *editor, const char *cmd) {
    char trimmed_cmd[MAX_FILE_NAME + 16];
    sscanf(cmd, "%s", trimmed_cmd);

    if (is_same(trimmed_cmd, "a")) {
        cmdAppend(editor);
    } else if (is_same(trimmed_cmd, "i")) {
        cmdInsert(editor);
    } else if (is_same(trimmed_cmd, "c")) {
        cmdReinput(editor);
    } else if (is_same(trimmed_cmd, "rm")) {
        int begin, end;
        int ret = sscanf(cmd, "%*s%d,%d", &begin, &end);
        if (ret == 1)
            cmdDelete(editor, begin, begin);
        else if (ret == 2)
            cmdDelete(editor, begin, end);
        else {
            error("Error rm Usage!");
        }
    } else if (is_same(trimmed_cmd, "ls")) {
        int begin, end;
        int ret = sscanf(cmd, "%*s%d,%d", &begin, &end);
        if (ret == 1)
            cmdDisplay(editor, begin, begin);
        else if (ret == 2)
            cmdDisplay(editor, begin, end);
        else {
            error("Error ls Usage!");
        }
    } else if (is_same(trimmed_cmd, "la")) {
        cmdDisplay(editor, 1, editor->totalLine);
    } else if (is_same(trimmed_cmd, "r")) {
        char filename[MAX_FILE_NAME + 1];
        sscanf(cmd, "%*s%s", filename);
        cmdRead(editor, filename);
    } else if (is_same(trimmed_cmd, "w")) {
        char filename[MAX_FILE_NAME + 1];
        sscanf(cmd, "%*s%s", filename);
        cmdWrite(editor, filename);
    } else if (is_same(trimmed_cmd, "h")) {
        usage();
    } else if (is_same(trimmed_cmd, "q")) {
        // TODO: 正确释放所有申请的内存
        printf("GoodBye!\n");
        exit(EXIT_SUCCESS);
    } else if (isdigit(trimmed_cmd[0])){
        char *endptr = NULL;
        int new_line = strtol(cmd, &endptr, 10);
        if (*endptr == '\0') {
            cmdChangeLine(editor, new_line);
        } else {
            error("Bad/Unknown command %s", cmd);
        }
    } else {
        // TODO: 错误报告
    }
}

void cmdAppend(Editor *editor) {
    printf("It\'s input mode now. Quit with a line with a single dot(.)\n");
    char lineBuffer[ONE_LINE_MAX_SIZE + 1];
    gets(lineBuffer);
    // TODO: 如果有需要，可以添加你需要的变量
    while(!is_same(lineBuffer, ".")) {
        // TODO: 正确使用 insertLine 等函数来实现插入，并正确更新 currentLine 和 totalLine
        gets(lineBuffer);
    }
}

void cmdInsert(Editor *editor) {
    printf("It\'s input mode now. Quit with a line with a single dot(.)\n");
    char lineBuffer[ONE_LINE_MAX_SIZE + 1];
    gets(lineBuffer);
    // TODO: 如果有需要，可以添加你需要的变量
    while(!is_same(lineBuffer, ".")) {
        // TODO: 正确使用 insertLine 等函数来实现插入，并正确更新 currentLine 和 totalLine
        gets(lineBuffer);
    }
}

void cmdReinput(Editor *editor) {
    // TODO: 正确使用 editLine 等函数实现函数功能
}

void cmdChangeLine(Editor *editor, int new_line) {
    // TODO: 正确实现该等函数的功能与错误报告
}

void cmdDisplay(Editor *editor, int begin, int end) {
    // TODO: 正确使用 displayLine 等函数实现函数功能，并且实现错误报告
}

void cmdDelete(Editor *editor, int begin, int end) {
    // TODO: 正确使用 deleteLine 等函数实现函数功能，并且实现错误报告
}

void cmdWrite(Editor *editor, const char *filename) {
    // TODO: 正确使用 writeFile 等函数实现函数功能，并且实现错误报告 （选做）
}

void cmdRead(Editor *editor, const char *filename) {
    // TODO: 正确使用 readFile 等函数实现函数功能，并且实现错误报告 （选做）
}

void usage(void) {
    printf("Command:\n"
           "\ta                Append text to the buffer after the current addressed line\n"
           "\ti                Insert text in the buffer before the current addressed line\n"
           "\tc                Reinput the current addressed line\n"
           "\tq                Exit the editor\n"
           "\th                Show help message\n"
           "\t[number]         set the current addressed line to [number]\n"
           "\tr [file]         Read file to the current buffer\n"
           "\tw [file]         Write all lines to file\n"
           "\trm [begin],[end] Delete the addressed lines from the buffer\n"
           "\tls [begin],[end] Print the addressed lines\n"
           "\tla [begin],[end] Print all the lines in the current buffer\n"
            );
}

// 以下都是 error 函数的实现，不要求看懂

#include <stdarg.h>
#if defined(_WIN16) | defined(_WIN32) | defined(_WIN64)
#include <windows.h>
#define IS_WIN
#endif

void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
#ifdef IS_WIN
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    fprintf(stderr, "\x1b[1;37;41m");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\x1b[0m\n");
    va_end(args);
}

