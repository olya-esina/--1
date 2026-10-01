#include <stdio.h>
#include <windows.h>

int *find_min(int *begin, int *end){
    int *min = begin;

    for (int *ptr = begin; ptr < end; ptr++){
        if (*ptr < *min){
            min = ptr;
        }
    }

    return min;
}

int *find_max(int *begin, int *end){
    int *max = begin;

    for (int *ptr = begin; ptr < end; ptr++){
        if (*ptr > *max){
            max = ptr;
        }
    }
    return max;
}

long long sum_between(const int *first, const int *second){
    const int *left;
    const int *right;
    long long sum = 0;
    const int *p;

    if (first > second){
        left = second;
        right = first;
    } else{
        left = first;
        right = second;
    }
    p = left + 1;
    while (p < right){
        sum += *p;
        ++p;
    }
    return sum;
}

size_t find_longest_increasing(int *begin, int *end, int **sequence_begin){
    size_t max_len = 1;
    size_t curr_len = 1;
    *sequence_begin = begin;

    for (int *ptr = begin; ptr + 1 < end; ptr++){
        if (*ptr < *(ptr + 1)) curr_len++;
        else curr_len =1;
        if (curr_len > max_len){
            max_len = curr_len;
            *sequence_begin = ptr - curr_len +2;
        }
    }
    return max_len;
}

void reverse_range(int *begin, int *end){
    int *left;
    int *right;
    int tmp;

    if (begin == end) return;

    left = begin;
    right = end - 1;
    while (left < right){
        tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}

void print_array(const int *begin, const int *end){
    const int *p = begin;
    while (p < end){
        printf("%d", *p);
        ++p;
        if (p < end) printf(" ");
    }
    printf("\n");
}


//Проверка, вывод

int main(void){
    
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    int i;
    int arr[1000];
    int *begin;
    int *end;
    int *pmin;
    int *pmax;
    long long imin, imax, dist;
    long long s;
    int *seq_begin;
    size_t seq_len;

    printf("Введите количество элементов (2.. 1000):");
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000){
        printf("Некоректное количество элементов.\n");
        return 1;
    }

    printf("Введите %d целых чисел: ", n);
    for (i = 0; i < n; ++i){
        if (scanf("%d", &arr[i]) != 1){
            printf("Ошибка ввода.\n");
            return 1;
        }
    }

   begin = arr;
   end = arr + n;
   pmin = find_min(begin, end);
   pmax = find_max(begin, end);
   imin = (long long)(pmin - begin);
   imax = (long long)(pmax - begin);
   dist = (imin > imax) ? (imin -imax):(imax - imin);
   s = sum_between(pmin, pmax);

    printf("Исходный массив:\n");
    print_array(begin, end);

    printf("Минимум: %d\n", *pmin);
    printf("Позиция минимума: %lld\n", imin);
    printf("Максимум: %d\n", *pmax);
    printf("Позиция максимума: %lld\n", imax);
    printf("Расстояние между минимумом и максимумом: %lld\n", dist);
    printf("Сумма элементов между минимумом и максимумом: %lld\n", s);

    seq_begin = begin;
    seq_len = find_longest_increasing(begin, end, &seq_begin);

    printf("Самый длинный возрастающий участок:\n");
    print_array(seq_begin, seq_begin + seq_len);
    printf("Длина: %zu\n", seq_len);

    reverse_range(seq_begin, seq_begin + seq_len);

    printf("Массив после разворота выбранного участка:\n");
    print_array(begin, end);

    return 0;
}