/*
一元稀疏多项式计算器
侯超群  PB21111618
*/

#include "Polynomial.h"

//进行多项式的输入处理
void CreatPolyn(Polynomial List)
{
  List->next = NULL;
  Polynomial p, p_pre; //辅助节点,前驱结点
  //依次输入系数,指数
  CoefType x;
  ExpnType y;

  while (OK)
  {
    //输入形式比如3x^2,输入3 2\n
    scanf("%f ", &x); //输入系数
    scanf("%d", &y);  //输入指数

    //在创建新节点时对链表中指数进行排序，使其序列按指数降序排列
    Polynomial q = (Polynomial)malloc(sizeof(Polynomial));
    q->coef = x;
    q->expn = y;

    //每次从头结点后向后查找比较
    p = List->next;
    p_pre = List;
    //第一次插入
    if (p == NULL)
    {
      List->next = q;
      q->next = p;
    }
    //进行查找排序
    while (p_pre != NULL)
    {
      //插入到最后面
      if (p == NULL)
      {
        p_pre->next = q;
        q->next = p;
        break;
      }
      //插入到该节点的前面
      if (q->expn > p->expn)
      {
        q->next = p;
        p_pre->next = q;
        break;
      }
      //如果指数相等
      else if (q->expn == p->expn)
      {
        p->coef += q->coef;
        break;
      }
      //继续向后查找
      else
      {
        p_pre = p;
        p = p->next;
      }
    }
    char c = getchar();
    if (c == '\n')
      break;
  }
}

//完成多项式相加运算
Polynomial AddPolyn(Polynomial Pa, Polynomial Pb)
{
  Polynomial Pab = (Polynomial)malloc(sizeof(Polynomial)); // Pa+Pb的返回多项式头结点
  Polynomial m = Pab;
  Polynomial p = Pa->next;
  Polynomial q = Pb->next;
  // p, q均为Pa,Pb的头指针

  while (p || q)
  {
    Polynomial n = (Polynomial)malloc(sizeof(Polynomial));
    m->next = n;
    m = m->next;
    if (p == NULL && q != NULL)
    {
      m->coef = q->coef;
      m->expn = q->expn;
      q = q->next;
    }
    else if (p != NULL && q == NULL)
    {
      m->coef = p->coef;
      m->expn = p->expn;
      p = p->next;
    }
    else
    {
      if (p->expn == q->expn)
      {
        m->coef = p->coef + q->coef;
        m->expn = p->expn;
        p = p->next;
        q = q->next;
      }
      else if (p->expn > q->expn)
      {
        m->coef = p->coef;
        m->expn = p->expn;
        p = p->next;
      }
      else if (p->expn < q->expn)
      {
        m->coef = q->coef;
        m->expn = q->expn;
        q = q->next;
      }
    }
  }
  m->next = NULL;
  return Pab;
}

//完成多项式相减运算,Pa-Pb
Polynomial SubtractPolyn(Polynomial Pa, Polynomial Pb)
{
  Polynomial Pab = (Polynomial)malloc(sizeof(Polynomial)); // Pa-Pb的返回多项式头结点
  Polynomial m = Pab;
  Polynomial p = Pa->next;
  Polynomial q = Pb->next;
  // p, q均为Pa,Pb的头指针

  while (p || q)
  {
    Polynomial n = (Polynomial)malloc(sizeof(Polynomial));
    m->next = n;
    m = m->next;
    if (p == NULL && q != NULL)
    {
      m->coef = -q->coef;
      m->expn = q->expn;
      q = q->next;
    }
    else if (p != NULL && q == NULL)
    {
      m->coef = p->coef;
      m->expn = p->expn;
      p = p->next;
    }
    else
    {
      if (p->expn == q->expn)
      {
        m->coef = p->coef - q->coef;
        m->expn = p->expn;
        p = p->next;
        q = q->next;
      }
      else if (p->expn > q->expn)
      {
        m->coef = p->coef;
        m->expn = p->expn;
        p = p->next;
      }
      else if (p->expn < q->expn)
      {
        m->coef = -q->coef;
        m->expn = q->expn;
        q = q->next;
      }
    }
  }
  m->next = NULL;
  return Pab;
}

//建立乘积多项式Pa Pb
Polynomial MultiplyPolyn(Polynomial Pa, Polynomial Pb)
{
  Polynomial Pab = (Polynomial)malloc(sizeof(Polynomial)); //返回乘积式
  Polynomial m = Pab;
  //初始化Pab为0
  Polynomial n = (Polynomial)malloc(sizeof(Polynomial));
  m->next = n;
  m = m->next;
  m->coef = 0;
  m->expn = 0;
  m->next = NULL;
  Polynomial PabF = (Polynomial)malloc(sizeof(Polynomial)); //辅助乘积式
  Polynomial mf = PabF;
  Polynomial p = Pa->next;
  Polynomial q = Pb->next;
  // p,q均为Pa,Pb的头指针

  while (q)
  {
    while (p)
    {
      Polynomial n = (Polynomial)malloc(sizeof(Polynomial));
      mf->next = n;
      mf = mf->next;
      mf->coef = p->coef * q->coef;
      mf->expn = p->expn + q->expn;
      p = p->next;
    }
    mf->next = NULL;
    p = Pa->next;
    Pab = AddPolyn(Pab, PabF);
    //初始化PabF为空，释放内存
    mf = PabF->next;
    Polynomial mf_next = mf->next;
    while (mf_next)
    {
      free(mf);
      mf = mf_next;
      mf_next = mf_next->next;
    }
    free(mf);
    mf = PabF;
    q = q->next;
  }
  return Pab;
}

//计算多项式在x处的值
CoefType CalcuX(Polynomial List, CoefType x)
{
  CoefType result = 0;       //记录多项式在x处的值
  Polynomial p = List->next; // p此时为头指针
  while (p != NULL)
  {
    result += p->coef * pow(x, p->expn);
    p = p->next;
  }
  return result;
}

//计算多项式List的导函数List'
Polynomial CalcuDeriva(Polynomial List)
{
  Polynomial D_List = (Polynomial)malloc(sizeof(Polynomial)); //返回导函数的表达式
  Polynomial p = List->next;                                  // p此时指向原函数头指针
  Polynomial q = D_List;
  while (p != NULL)
  {
    Polynomial m = (Polynomial)malloc(sizeof(Polynomial));
    q->next = m;
    q = q->next;
    //如果指数为零
    if (p->expn == 0)
    {
      q->coef = 0;
      q->expn = 0;
    }
    else
    {
      q->coef = p->coef * p->expn;
      q->expn = p->expn - 1;
    }
    p = p->next;
  }
  q->next = NULL;
  return D_List;
}

//进行多项式的输出操作，并按降序排列
void PrinPolyn(Polynomial List)
{
  Polynomial p = List->next;

  //清除链表前面系数为零的节点，便于首位无符号输出，同时考虑结果为零的链表
  while (p->coef == 0 && p->next != NULL)
    p = p->next;

  if (p->expn == 0 || p->coef == 0)
    printf("%g", p->coef);
  else if (p->expn == 1 && p->coef != 1)
    printf("%gx", p->coef);
  else if (p->coef == 1 && p->expn != 1)
    printf("x^%d", p->expn);
  else if (p->coef == 1 && p->expn == 1)
    printf("x");
  else if (p->coef == -1 && p->expn != 1)
    printf("-x^%d", p->expn);
  else if (p->coef == -1 && p->expn == 1)
    printf("-x");
  else
    printf("%gx^%d", p->coef, p->expn);
  p = p->next;
  while (p != NULL)
  {
    if (p->coef == 0)
    {
      p = p->next;
      continue;
    }
    else
    {
      if (p->expn == 0)
        printf("%+g", p->coef);
      else if (p->expn == 1 && p->coef != 1 && p->coef != -1)
        printf("%+gx", p->coef);
      else if (p->coef == 1 && p->expn != 1)
        printf("+x^%d", p->expn);
      else if (p->coef == 1 && p->expn == 1)
        printf("+x");
      else if (p->coef == -1 && p->expn != 1)
        printf("-x^%d", p->expn);
      else if (p->coef == -1 && p->expn == 1)
        printf("-x");
      else
        printf("%+gx^%d", p->coef, p->expn);
    }
    p = p->next;
  }
  printf("\n");
}

int main()
{
  printf("************操作说明************\n");

  printf("输入'a',执行Pa+Pb,返回多项式P并打印\n");
  printf("输入's',执行Pa-Pb,返回多项式P并打印\n");
  printf("输入'd',执行对Pa求其导函数,返回多项式D_P并打印\n");
  printf("输入'x',请输入一个值,返回多项式Pa在该点的值并打印\n");
  printf("输入'm',执行Pa*Pb,返回多项式P并打印\n");
  printf("输入'#',终止操作\n");

  printf("*******************************\n");

  printf("请以系数 指数 系数 指数~的形式输入多项式Pa\n");
  Polynomial Pa = (Polynomial)malloc(sizeof(Polynomial));
  CreatPolyn(Pa);
  printf("打印多项式Pa如下:\n");
  PrinPolyn(Pa);

  printf("请以系数 指数 系数 指数~的形式输入多项式Pb\n");
  Polynomial Pb = (Polynomial)malloc(sizeof(Polynomial));
  CreatPolyn(Pb);
  printf("打印多项式Pb如下:\n");
  PrinPolyn(Pb);

  printf("请输入操作指令\n");

  Polynomial P, D_P;
  int x0;
  char choose;
  while (((choose = getchar()) != '#'))
  {
    switch (choose)
    {
    case 'a':
      P = AddPolyn(Pa, Pb);
      printf("Pa+Pb结果多项式表示为:\n");
      PrinPolyn(P);
      break;
    case 's':
      P = SubtractPolyn(Pa, Pb);
      printf("Pa-Pb结果多项式表示为:\n");
      PrinPolyn(P);
      break;
    case 'd':
      D_P = CalcuDeriva(Pa);
      printf("Pa导函数多项式表示为:\n");
      PrinPolyn(D_P);
      break;
    case 'x':
      printf("请输入需要计算处x0的值\n");
      scanf("%d", &x0);
      int X = CalcuX(Pa, x0);
      printf("多项式Pa在%d处的值为%d\n", x0, X);
      break;
    case 'm':
      P = MultiplyPolyn(Pa, Pb);
      printf("Pa*Pb结果多项式表示为:\n");
      PrinPolyn(P);
      break;
    default:
      break;
    }
  }
  free(Pa);
  free(Pb);
  printf("****************************\n");
  return 0;
}