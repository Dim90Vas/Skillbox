/*- Объявите массив из пяти элементов и заполните его произвольной последовательностью.
- Выведите массив в консоль в строку, используя цикл и указатели.
- С помощью цикла и используя только указатель на массив, выстройте все элементы массива
в порядке возрастания, не обращаясь к элементам массива через индекс, а именно через указатели.*/
#include <stdio.h>
#define INT_N 5
int main() {
    int arr[INT_N];
    for(int i=0; i<INT_N; ++i)
        scanf("%d", (arr+i));

    for(int i=0; i<INT_N; ++i)
        printf("%d ", *(arr+i));
    printf("\n");

    int min = *arr;
    int max = *arr;
    int index=0;
    int n=0;

    for(int i=0; i<INT_N; ++i) {
        if(*(arr+i)>max) {
            max=*(arr+i);
        }
    }

    while(n<INT_N) {
        min=*(arr);
        for(int i=0; i<INT_N; ++i) {
            if(*(arr+i)<=min) {
                min=*(arr+i);
                index=i;
            }
        }
        printf("%d ", *(arr+index));
        *(arr+index)=max;
    ++n;
    }
    return 0;
}
