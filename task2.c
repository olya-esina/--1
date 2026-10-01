#include <stdio.h>
#include <stddef.h>
#include <locale.h>

double row_average(size_t cols, const int *row);

void print_matrix(size_t rows, size_t cols, const int matrix[rows][cols]){
    size_t i, j;
    for (i = 0; i < rows; ++i){
        const int *row = *(matrix + i);
        for (j = 0; j < cols; ++j){
            printf("%4d", *(row + j));
        }
        printf("\n");
    }
}

const int *find_matrix_max(size_t rows, size_t cols, const int matrix[rows][cols], size_t *max_row, size_t *max_col){
    const int *best = *(matrix + 0);
    size_t i;
    *max_row = 0;
    *max_col = 0;

    for (i =0; i < rows; ++i){
        const int *row = *(matrix + i);
        const int *p = row;
        const int *end = row + cols;
        while (p < end){
            if (*p > *best){
                best = p;
                *max_row = i;
                *max_col = (size_t)(p - row);
            }
            ++p;
        }
    }
    return best;
}

double matrix_average(size_t rows, size_t cols, const int matrix[rows][cols]){
    long long sum = 0;
    size_t i;
    for (i = 0; i < rows; ++i){
        const int *row = *(matrix + i);
        const int *p = row;
        const int *end = row + cols;
        while (p < end){sum += *p; ++p;}
    }
    return (double)sum/(double)(rows * cols);
}

size_t count_above_average(size_t rows, size_t cols, const int matrix[rows][cols], double average){
    size_t count = 0;
    size_t i;
    for (i = 0; i < rows; ++i){
        const int *row = *(matrix + i);
        const int *p = row;
        const int *end =row + cols;
        while (p < end){
            if ((double)*p > average)++count;
            ++p;
        }
    }
    return count;
}

size_t hottest_row(size_t rows, size_t cols, const int matrix[rows][cols]){
    size_t best = 0;
    size_t i;
    double best_avg = row_average(cols, *(matrix + 0));
    for (i = 1; i < rows; ++i){
        double a = row_average(cols, *(matrix + i));
        if (a > best_avg){best_avg = a; best = i;}
    }
    return best;
}

double row_average(size_t cols, const int *row){
    long long sum = 0;
    const int *p = row;
    const int *end = row + cols;
    while (p < end){sum += *p; ++p;}
    return (double)sum/(double)cols;
}

void fill_row_with_average(size_t cols, int *row){
    long long sum = 0;
    int *p = row;
    int *end = row + cols;
    int avg;

    while (p < end){sum += *p; ++p;}
    avg = (int)((double)sum/(double)cols);

    p = row;
    while (p < end){*p = avg; ++p;}
}

int max_neighbor_difference(size_t rows, size_t cols, const int matrix[rows][cols]){
    int best = 0;
    size_t i;
    for (i = 0; i < rows; ++i){
        const int *row = *(matrix + i);
        const int *p = row;
        const int *end = row + cols - 1;
        while (p < end){
            int diff = *(p + 1) - *p;
            if (diff < 0) diff = -diff;
            if (diff > best) best = diff;
            ++p;
        }
    }
    return best;
}

//Проверка, вывод
#include <windows.h>
int main(void){
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    size_t R, C;
    size_t i, j;
    int matrix[50][50];
    size_t max_row = 0, max_col = 0;
    const int *pmax;
    double avg;
    size_t above;
    size_t hot;
    int md;

    printf("\n");
    if (scanf("%zu %zu", &R, &C)!= 2 ||R < 2||R > 50||C < 2||C > 50){
        printf(".\n");
        return 1;
    }

    printf("Введите %zu x %zu температуру:\n", R, C);
    for (i = 0; i < R; ++i){
        int *row = *(matrix + i);
        for (j = 0; j < C; ++j){
            if (scanf("%d", row + j)!= 1){
                printf("Ошибка ввода.\n");
                return 1;
            }
        }
    }

    printf("\nИсходная карта:\n");
    print_matrix(R, C, matrix);

    pmax = find_matrix_max(R, C, matrix, &max_row, &max_col);
    printf("\nМаксимальная температура: %d\n", *pmax);
    printf("Строка: %zu\n", max_row);
    printf("Столбец: %zu\n", max_col);

    avg = matrix_average(R, C, matrix);
    printf("Средняя температура карты: %2f\n", avg);

    above = count_above_average(R, C, matrix, avg);
    printf("Количество значений выше среднего: %zu\n", above);

    hot = hottest_row(R, C, matrix);
    printf("Строка с максимальным средним: %zu\n", hot);
    printf("Среднее выбранной строки: %2f\n", row_average(C, *(matrix + hot)));

    fill_row_with_average(C, *(matrix + hot));

    printf("\nКарта после замены выбранной строки:\n");
    print_matrix(R, C, matrix);

    md = max_neighbor_difference(R, C, matrix);
    printf("\nМаксимальная разница соседних температур: %d\n", md);

    return 0;
}