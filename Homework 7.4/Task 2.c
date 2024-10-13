#include <stdio.h>
#include <stdlib.h>
/*Дан массив A[10]. Необходимо заполнить массив и вывести его максимальное значение, а также номер элемента максимального значения.*/
int main() {
    int A[10];
    int max_ch=A[0], index;
    printf("Fill the array: \n");
    for(int i=0; i<10; ++i) {
        scanf("%d",&A[i]);
    }
    for(int i=0; i<10; ++i) {
        if(A[i]>max_ch) {
            max_ch=A[i];
            index=i;
        }
    }
    printf("%d \t %d", max_ch, index);
    return 0;
}
