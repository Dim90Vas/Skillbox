#include <stdlib.h>
#include <stdio.h>
#define PROG 2
#if PROG == 1
/*Задание 1
Вам необходимо составить программу, которая с помощью функций библиотеки stdlib.h выделяет память для динамического массива,
размерность которого вводится с консоли. Массив также заполняется с консоли, далее заполненный массив выводится на консоль
поэлементно в строку. После вывода массива необходимо освободить память функцией из stdlib.h, далее заново попробовать вывести этот массив.*/

int main() {
    int size_arr;
    scanf("%d",&size_arr);
    int *arr = malloc(size_arr * sizeof(int));
    for(int i=0; i<size_arr; i++) {
        scanf("%d",(arr+i));
    }
    for(int i=0; i<size_arr; i++) {
        printf("%d ",*(arr+i));
    }
    free(arr);
    printf("\n");
    for(int i=0; i<size_arr; i++) {
        printf("%d ",*(arr+i));
    }
    return 0;
}
#elif PROG == 2
/*Вам необходимо составить программу, которая, не используя функций библиотеки stdlib.h, выделяет память для динамического массива,
размерность которого вводится с консоли. Массив также заполняется с консоли, далее заполненный массив выводится на консоль поэлементно в строку.
После вывода массива надо освободить память, не пользуясь функцией стандартной библиотеки по работе с памятью, далее заново попробовать вывести этот массив.*/
int mass[10000];

int *mymalloc(int size_arr) {
    for(int i=0; i<size_arr; i++) {
        scanf("%d",&mass[i]);
    }
    return mass;
}


int *myfree(int *arr) {
    for(int i=0; i<sizeof(arr)-1; i++) {
        *(arr+i)="";
    }
}

int main() {
    int size_arr;
    scanf("%d",&size_arr);
    int *arr = mymalloc(size_arr);
    for(int i=0; i<size_arr; i++) {
        printf("%d ",*(arr+i));
    }
    myfree(arr);
    for(int i=0; i<size_arr; i++) {
        printf("%d ",*(arr+i));
    }
    return 0;
}
#endif // PROG
