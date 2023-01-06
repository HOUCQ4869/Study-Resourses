/*
一元稀疏多项式计算器
侯超群  PB21111618
*/

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0;

typedef float CoefType; //定义系数数据类型
typedef int ExpnType;   //定义指数数据类型

//结点类型
typedef struct LNode
{
  CoefType coef; //系数
  ExpnType expn; //指数
  struct LNode *next;
} * Polynomial;

#endif
