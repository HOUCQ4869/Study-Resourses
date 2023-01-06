#include <cstdint>
#include <iostream>
#include <fstream>

#define MAXLEN 100
#ifndef LENGTH
#define LENGTH 3
#endif

int16_t lab1(int16_t a, int16_t b)
{
  // initialize
  int16_t output = 0, test_bit = 1;
  // calculation
  for (; b > 0; b--)
  {
    if ((a & test_bit) != 0)
    { // 测试位为1
      output++;
    }
    test_bit = test_bit + test_bit;
  }
  // return value
  return output;
}

int16_t lab2(int16_t p, int16_t q, int16_t n)
{
  // initialize
  int16_t F = 1, FP = 1, FPP = 1; // F(N), F(N-1), F(N-2)
  // calculation
  for (; n > 1; n--)
  {
    FPP = FP;
    FP = F;
    int16_t fp = FP, fpp = FPP;
    while (fp > 0)
      fp -= q;
    fp += q;
    while (fpp > 0)
      fpp -= p;
    fpp += p;
    F = fpp + fp;
  }
  // return value
  return F;
}

int16_t lab3(int16_t n, char s[])
{
  // initialize
  int16_t Max_length = 1, length = 1;
  char *p = s;
  // calculation
  for (; n > 1; n--)
  {
    if (*p == *(p + 1))
    {
      length++;
    }
    else
    { // 初始化length
      length = 1;
    }
    if (length > Max_length)
      Max_length = length;
    p++;
  }
  // return value
  return Max_length;
}

void lab4(int16_t score[], int16_t *a, int16_t *b)
{
  // initialize
  int16_t *p = score;
  *a = *b = 0;
  // calculation
  for (int i = 0; i < 16; i++)
  {
    int16_t min = 100, min_location = 0;
    for (int j = i + 1; j < 16; j++)
    {
      if (*(p + j) < min)
      {
        min = *(p + j);
        min_location = j;
      }
    }
    if (min < *(p + i))
    { // 交换最小值
      *(p + min_location) = *(p + i);
      *(p + i) = min;
    }
  }
  for (int i = 15; i > 11; i--)
  {
    if (*(p + i) >= 85)
      (*a)++;
    else if (*(p + i) >= 75)
      (*b)++;
  }
  for (int i = 11; i > 7; i--)
  {
    if (*(p + i) >= 75)
      (*b)++;
  }
}

int main()
{
  std::fstream file;
  file.open("test.txt", std::ios::in);

  // lab1
  int16_t a = 0, b = 0;
  for (int i = 0; i < LENGTH; i++)
  {
    file >> a >> b;
    std::cout << lab1(a, b) << std::endl;
  }

  // lab2
  int16_t p = 0, q = 0, n = 0;
  for (int i = 0; i < LENGTH; i++)
  {
    file >> p >> q >> n;
    std::cout << lab2(p, q, n) << std::endl;
  }

  // lab3
  char s[MAXLEN];
  for (int i = 0; i < LENGTH; i++)
  {
    file >> n >> s;
    std::cout << lab3(n, s) << std::endl;
  }

  // lab4
  int16_t score[16];
  for (int i = 0; i < LENGTH; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      file >> score[j];
    }
    lab4(score, &a, &b);
    for (int j = 0; j < 16; j++)
    {
      std::cout << score[j] << " ";
    }
    std::cout << std::endl
              << a << " " << b << std::endl;
  }

  file.close();
  return 0;
}