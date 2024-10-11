#include <stdio.h>
#include <stdlib.h>
/*Дан массив A[5]. Необходимо заполнить массив и вывести его среднее значение.*/
int main() {
    int A[5];
    printf("Fill the array: ");
    for(int i=0; i<5; ++i) {
        scanf("%d",&A[i]);
    }
    int x=0;
    for(int i=0; i<5; ++i) {
        x+=A[i];
    }
    printf("%d", x/5);
    return 0;
}
