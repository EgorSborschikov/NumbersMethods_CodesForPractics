#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define EPS 0.01

// Прототипы функций (для предотвращения неявного объявления)
void matrixVectorProduct(double** matrix, double* vector, double* result, int n);
void normalizeVector(double* vector, int n);
void calculateEigen(double** matrix, int n);
void calculateSpectralRadius(double** matrix, int n);
void displayInterface();

int main()
{
    setlocale(LC_ALL, "");

    displayInterface();

    return 0;
}

void matrixVectorProduct(double** matrix, double* vector, double* result, int n)
{
    for (int i = 0; i < n; i++)
    {
        result[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void normalizeVector(double* vector, int n)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        norm += vector[i] * vector[i];
    }
    norm = sqrt(norm);
    for (int i = 0; i < n; i++)
    {
        vector[i] /= norm;
    }
}

void calculateEigen(double** matrix, int n)
{
    double* eigenvalues = (double*)malloc(n * sizeof(double));
    double** eigenvectors = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        eigenvectors[i] = (double*)malloc(n * sizeof(double));
    }

    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        eigenvectors[i][i] = 1.0;
        x[i] = 1.0;
    }

    double lambda = 0.0;
    double lambda_prev = 1.0;

    while (fabs(lambda - lambda_prev) > EPS)
    {
        lambda_prev = lambda;

        matrixVectorProduct(matrix, x, y, n);
        normalizeVector(y, n);

        for (int i = 0; i < n; i++)
        {
            x[i] = y[i];
        }

        matrixVectorProduct(matrix, y, x, n);

        lambda = 0.0;
        for (int i = 0; i < n; i++)
        {
            lambda += x[i] * y[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        eigenvalues[i] = x[i];
    }

    // Обновляем собственные векторы матрицы
    for (int i = 0; i < n; i++)
    {
        matrixVectorProduct(matrix, eigenvectors[i], x, n);
        normalizeVector(x, n);
        for (int j = 0; j < n; j++)
        {
            eigenvectors[i][j] = x[j];
        }
    }

    printf("Собственные значения:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", eigenvalues[i]);
    }
    printf("\n");

    printf("Собственные векторы:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f ", eigenvectors[i][j]);
        }
        printf("\n");
    }

    free(eigenvalues);
    free(x);
    free(y);
    for (int i = 0; i < n; i++)
    {
        free(eigenvectors[i]);
    }
    free(eigenvectors);
}


void calculateSpectralRadius(double** matrix, int n)
{
    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));

    // Инициализируем вектор x единичными значениями
    for (int i = 0; i < n; i++)
    {
        x[i] = 1.0;
    }

    double maxEigenvalue = 0.0;
    double prevMaxEigenvalue = 0.0;

    // Итерационный процесс для вычисления спектрального радиуса
    do
    {
        prevMaxEigenvalue = maxEigenvalue;

        // Вычисляем произведение матрицы на вектор
        matrixVectorProduct(matrix, x, y, n);

        // Находим максимальное значение по модулю в векторе y
        maxEigenvalue = fabs(y[0]);
        for (int i = 1; i < n; i++)
        {
            if (fabs(y[i]) > maxEigenvalue)
            {
                maxEigenvalue = fabs(y[i]);
            }
        }

        // Нормализуем вектор x
        for (int i = 0; i < n; i++)
        {
            x[i] = y[i] / maxEigenvalue;
        }
    } while (fabs(maxEigenvalue - prevMaxEigenvalue) > EPS);

    printf("Спектральный радиус: %.2f\n", maxEigenvalue);

    free(x);
    free(y);
}

void displayInterface()
{
    printf("Добро пожаловать в программу для работы с матрицами!\n");

    int n;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &n);
    
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }

    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    int choice;
    while (1)
    {
        printf("1. Найти собственные значения и собственные векторы матрицы\n");
        printf("2. Определить спектральный радиус матрицы\n");
        printf("3. Выйти\n");

        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                calculateEigen(matrix, n);
                break;
            case 2:
                calculateSpectralRadius(matrix, n);
                break;
            case 3:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    }

    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}