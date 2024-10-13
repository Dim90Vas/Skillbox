#include <stdio.h>
#include <stdlib.h>

#define N 10
/*Даны целочисленные массивы X[10], Y[10]. Каждый массив необходимо преобразовать по правилу:
Если компоненты массива упорядочены по возрастанию, все положительные компоненты следует заменить на значение 0,
в противном случае массивы оставить без изменений.
В этой задаче нужно написать программу, выполняющую следующие действия:
-Ввод исходных массивов X и Y.
-Вывод на экран исходных массивов.
-Преобразование массивов.
-Вывод на экран изменённых массивов.*/
void func_transformation(int arr[]) {
    int x=0;
    for(int i=0; i<N; ++i) {
        if(arr[i]<arr[i+1]) {
            x++;
        }
    }
    if(x==N-1) {
        for(int i=0; i<N; ++i) {
            if(arr[i]>0) {
                arr[i]=0;
            }    
        }    
    }
}

void func_printing(int arr[]) {
    for(int i=0; i<N; ++i) {
        printf("%d ", arr[i]);
    }
}

int main() {
    //int X[N]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; Для примера
    //int Y[N]={8, 6, 4, 3, 4, 2, 5, 4, 4, 1};
    printf("Enter array X: ");
    for(int i=0; i<N; ++i) {
        scanf("%d", &X[i]);
    }
    printf("Enter array Y: ");
    for(int j=0; j<N; ++j) {
        scanf("%d", &Y[j]);
    }
    
    printf("\nArray X: ");
    func_printing(X);
    printf("\nArray Y: ");
    func_printing(Y);
    
    func_transformation(X);
    func_transformation(Y);

    printf("\nNew array X: ");
    func_printing(X);
    printf("\nNew array Y: ");
    func_printing(Y);
    return 0;
}
