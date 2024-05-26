#include <stdio.h>
#include <locale.h>
void LagrangeMethod(int n, int I, int j, float a, float l, float f, float x[], float y[]) {
    printf(«Задайте степень полинома: «);
    scanf(«%d», &n);
    printf(«Введите таблицу значений функции\n»);
    for (I = 0; I <= n; i++) {
        printf(“Введите x[%d] и y[%d]: “, I, i);
        scanf(“%f %f”, &x[i], &y[i]);
    }

    printf(«Введите значение аргумента, для которого требуется найти значение функции: «);
    scanf(“%f”, &a);
    f = 0;
    for (I = 0; I <= n; i++) {
        l = 1;
        for (j = 0; j <= n; j++) {
            if (j != i) {
                l *= (a – x[j]) / (x[i] – x[j]);
                
            }
            l *= y[i];
            f += l;
            
        }
    }
    printf(“При a=%.2f f=%.6e\n”, a, f);

}

int main() {
    setlocale(LC_ALL, “”);
    int n, I, j;
    float a, l, f;
    float x[10], y[10];
    LagrangeMethod(n, I, j, a, l, f, x, y);
    return 0;

}