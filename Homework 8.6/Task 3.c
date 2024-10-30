/*- Объявите массив из пяти элементов и заполните его произвольной последовательностью.
- Выведите массив в консоль в строку, используя цикл и указатели.
- С помощью цикла и используя только указатель на массив, найдите среднее значение массива,
медианное значение, а также его максимальное и минимальное значения.*/
#include <stdio.h>
#define INT_N 5
int main() {
    int arr[INT_N]; //={5,2,72,4,8};
    int arr_new[INT_N];
    int min = *arr;
    int max = *arr;
    int average_value=0;
    int median_value;
    int n=0;
    int index=0;
    for(int i=0; i<INT_N; ++i) {
        scanf("%d", &(*(arr+i)));
    }

    for(int i=0; i<INT_N; ++i) {
        printf("%d ", *(arr+i));
    }

    for(int i=0; i<INT_N; ++i) {
        average_value+=*(arr+i);
    }

    for(int i=0; i<INT_N; ++i) {
        if(*(arr+i)>max) {
            max=*(arr+i);
        }
    }
    for(int i=0; i<INT_N; ++i) {
        if(*(arr+i)<min) {
            min=*(arr+i);
        }
    }
    printf("\nMinimum value: %d", min);
    printf("\nMaximum value: %d", max);
    printf("\nAverage value: %d", average_value/5);

    while(n<INT_N) {
        min=*(arr);
        for(int i=0; i<INT_N; ++i) {
            if(*(arr+i)<=min) {
                min=*(arr+i);
                index=i;
            }
        }
        *(arr_new+n)=*(arr+index);
        *(arr+index)=max;
    ++n;
    }
    printf("\nMedian value: %d", *(arr_new+(INT_N/2)));
    return 0;
}
