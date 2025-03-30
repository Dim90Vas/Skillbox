#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 15 //количество чисел в карточке.
#define B 90 //количество бочонков

int comp(const void *a, const void *b) {
    int data1 = *(int *)a, data2 = *(int *)b;
    if(data1 < data2) // a < b
        return -1;
    else if(data1 == data2) // a == b
        return 0;
    else
        return 1;  // a > b
}

void barrels(int *barrel) {
    for(int i=0; i<B; i++) {
        barrel[i]=i+1;
    }
    for(int j=0; j<B; j++) {
        printf("%d ", barrel[j]);
    }
    printf("\n");
}

int bar(int *barrel) { //вытаскивание бочонка
    int b = 1+rand()%90;
    int k=0;
    for(int i=0; i<B; i++) {
        if(barrel[i]==b) {
            k=b;
            barrel[i]=0;
        }
    }
    if(k>0)
        return k;
    else
        return bar(barrel);
}

void check(int b, int *card, int *barrel) {
    for(int i=0; i<B; i++) {
        if(barrel[i]==b&&barrel[i]!=0) {
            barrel[i]=0;
        }
    }
    for(int j=0; j<M; j++) {
        if(card[j]==b) {
            card[j]=0;
        }
    }
}

void cardArr(int *card) { //игровая карточка
    for(int m=0; m<M; m++) {
        card[m]=1+rand()%90;
    }
    qsort(card, M, sizeof(int), comp);//сортировка массива
    for(int m=0; m<M; m++) {//исключение повторяющихся чисел
        if(card[m]==card[m+1])
            card[m+1]=1+rand()%90;
    }
    for(int m=0; m<M; m++) {//вывод карточки
        printf("%d  ", card[m]);
    }
    printf("\n");
}


int main() {
    srand(time(NULL));
    int card[M];
    int barrel[B];
    barrels(barrel);
    cardArr(card);
    int num=1;
    int p=0;
    do {
        p=0;
        scanf("%d", &num);
        int b = bar(barrel);
        printf("%d", b);
        check(b, card, barrel);

        printf("\n");
        for(int j=0; j<B; j++) {
            printf("%d ", barrel[j]);
        }
        printf("\n");
        for(int j=0; j<M; j++) {
            printf("%d ", card[j]);
        }
        printf("\n");

        for(int j=0; j<M; j++) {
            if(card[j]==0)
                p++;
        }
        if(p==M) {
            num=0;
            printf("Game over");
        }

    } while(num!=0);
    return 0;
}
