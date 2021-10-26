#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#define OPTIONS "sctea"
int main(int argc, char **argv) {

  bool SinTrue = false;
  bool CosTrue = false;
  bool TanTrue = false;
  bool ExpTrue = false;
  bool AllTrue = false;
  void Sin();
  void Cos();
  void Tan();
  void Exp();
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {

    case 's':
      SinTrue = true;
      break;
    case 'c':
      CosTrue = true;
      break;
    case 't':
      TanTrue = true;
      break;
    case 'e':
      ExpTrue = true;
      break;
    case 'a':
      AllTrue = true;
      break;
    }
  }

  if (argc == 1) {
    puts("An argument must be supplied");
    return -1;

  } else if (argc > 3) {
    puts("Only one argument allowed");
    return -1;
  }

  else if (SinTrue) {
    Sin();
  } else if (CosTrue) {
    Cos();
  } else if (TanTrue) {
    Tan();
  } else if (ExpTrue) {
    Exp();
  } else if (AllTrue) {
    Sin();
    Cos();
    Tan();
    Exp();
  }
}

void Sin() {
  printf(" x%3s\t Sin%6s\t Library%3s\t Difference\n", " ", " ", " ");
  printf(" -%3s\t ---%6s\t -------%3s\t ----------\n", " ", " ", " ");
  int i = 0;
  double x = -6.28318530718;
  for (i = 0; i < 65; i++) {

    double Sin =
        (x * (((x * x) * (52785432 - 479249 * (x * x)) - 1640635920) * (x * x) +
              11511339840)) /
        (((18361 * (x * x) + 3177720) * (x * x) + 277920720) * (x * x) +
         11511339840);
    double LibSin = sin(x);
    double Diff = Sin - LibSin;
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, Sin, LibSin, Diff);
    x += 0.19634954084;
  }
}

void Cos() {
  printf(" x%3s\t Cos%6s\t Library%3s\t Difference\n", " ", " ", " ");
  printf(" -%3s\t ---%6s\t -------%3s\t ----------\n", " ", " ", " ");
  int i = 0;
  double x = -6.28318530718;
  for (i = 0; i < 65; i++) {
    double Cos =
        ((((x * x) * (1075032 - 14615 * (x * x)) - 18471600) * (x * x) +
          39251520)) /
        (((127 * (x * x) + 16632) * (x * x) + 1154160) * (x * x) + 39251520);
    double LibCos = cos(x);
    double Diff = Cos - LibCos;
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, Cos, LibCos, Diff);
    x += 0.19634954084;
  }
}

void Tan() {
  printf(" x%3s\t Tan%6s\t Library%3s\t Difference\n", " ", " ", " ");
  printf(" -%3s\t ---%6s\t -------%3s\t ----------\n", " ", " ", " ");
  int i = 0;
  double x = -1.0471975512;
  for (i = 0; i < 12; i++) {
    double Tan =
        x *
        (((x * x) * (((x * x) - 990) * (x * x) + 135135) - 4729725) * (x * x) +
         34459425) /
        (((x * x) * ((45 * (x * x) - 13860) * (x * x) + 945945) - 16216200) *
             (x * x) +
         34459425);
    double LibTan = tan(x);
    double Diff = Tan - LibTan;
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, Tan, LibTan, Diff);
    x += 0.19634954084;
  }
}

void Exp() {
  printf(" x%3s\t Exp%6s\t Library%3s\t Difference\n", " ", " ", " ");
  printf(" -%3s\t ---%6s\t -------%3s\t ----------\n", " ", " ", " ");
  double epsilon = .000000001;
  double prin = 0;
  double val = 1;
  int n = 1;
  double x = 0;
  for (x = 0; x < 9; x += 0.1) {
    val = 1;
    prin = 0;
    n = 1;

    while (val > epsilon) {
      prin += val;
      val = (val * (x / n));
      n += 1;
    }
    double Libe = exp(x);
    double diff = prin - Libe;
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, prin, Libe, diff);
  }
}
