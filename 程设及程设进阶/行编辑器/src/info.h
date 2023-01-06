#pragma once

#include <stdio.h>
#include <stdarg.h>
#if defined(_WIN16) | defined(_WIN32) | defined(_WIN64)
#include <windows.h>
#define IS_WIN
#endif

static void __vte_print(const char *vte, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
#ifdef IS_WIN
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    printf("%s", vte);
    vprintf(fmt, args);
    printf("\x1b[0m");
    va_end(args);
}


#define __get_fmt_str(arg) \
    _Generic((arg), \
                      char: "%c", \
                signed int: "%d", \
              unsigned int: "%u", \
                  long int: "%ld", \
         unsigned long int: "%lu", \
             long long int: "%lld", \
    unsigned long long int: "%llu", \
                     float: "%g", \
                    double: "%g", \
                    char *: "%s", \
                    void *: "%p", \
         char[sizeof(arg)]: "%s", \
                   default: "<error>" \
)

#define __print_arg_value(arg) __vte_print("\x1b[1;33m", __get_fmt_str(arg), arg)

// 祖传递归宏展开 
#define __nargs_0(...) __nargs_1(__VA_ARGS__, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0)
#define __nargs_1(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ...) q

#define __eval_0(...) __eval_1(__eval_1(__eval_1(__eval_1(__VA_ARGS__))))
#define __eval_1(...) __eval_2(__eval_2(__eval_2(__eval_2(__VA_ARGS__))))
#define __eval_2(...) __VA_ARGS__

#define __print_0(...) __eval_0(__print_1(__VA_ARGS__))
#define __print_1(...) __print_2(__nargs_0(__VA_ARGS__), __VA_ARGS__)
#define __print_2(num, ...) __print_3(num, __VA_ARGS__)
#define __print_3(num, ...) __arg_##num(__VA_ARGS__)
#define __arg_1(arg) __args_info_1(arg)
#define __arg_2(arg, ...) __args_info_2(arg), __loop(__VA_ARGS__)
#define __loop(...) __loop_helper __empty_helper()()(__VA_ARGS__)
#define __loop_helper() __print_1
#define __empty_helper()

#define __print_file_and_line() __vte_print("\n\x1b[1;32m", "%s:%d:\n", __FILE__, __LINE__)
#define __args_info(...) (__print_0(__VA_ARGS__), printf("\n"))
#define __all_info(...) (__print_file_and_line(), __args_info(__VA_ARGS__))

#define __args_info_1(arg) __vte_print("\x1b[1;33m", "\t%s = ", #arg), __print_arg_value(arg)
#define __args_info_2(arg) __args_info_1(arg), printf("\n")

#define info(...) __all_info(__VA_ARGS__);
