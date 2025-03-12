#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//условие для сортировки
int comp(const void *a, const void *b) {
    int data1 = *(int *)a, data2 = *(int *)b;
    if(data1 < data2) // a < b
        return -1;
    else if(data1 == data2) // a == b
        return 0;
    else
        return 1;  // a > b
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");//Иницилизируем окно графики

    float x, y;
    int legthArr;
    scanf("%d", &legthArr);
    float *arr = malloc(legthArr * sizeof(float));//выделение памяти под массив

    for(int i=0; i<legthArr; i++) {//заполнение массива
        arr[i]=rand()%500;
    }
    qsort (arr, legthArr, sizeof(float), comp);//сортировка массива

    for(int j=0; j<legthArr; j++) {//вывод массива
        printf("%.2f ", arr[j]);
    }

    for(x=0;x<=500;x+=1) {//вывод чистого графика
        y = sin(x/10)*50;
        putpixel(x+10, y+60, WHITE);
    }

    int i=0;
    for(x=0;x<=500;x+=1) {//вывод графика с шумом
        y = sin(x/10)*50;
        if(arr[i]==x) {
            if(arr[i]==arr[i+1])
                i++;
            circle(arr[i]+10, y+240, 3);
            i++;

        } else {
            putpixel(x+10, y+240, YELLOW);
        }
    }
    free(arr);
    getch();
    closegraph();//закрываем поток
    return 0;
}
