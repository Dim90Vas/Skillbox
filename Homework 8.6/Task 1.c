/*
- Объявите переменную и присвойте ей какое-либо значение.
- Объявите указатель и присвойте ему значение адреса ранее объявленной переменной.
- Выведите значение адреса переменной и её текущее значение в консоль.
- Поменяйте значение переменной на новое произвольное значение через указатель.
- Выведите адрес переменной и новое значение в консоль.*/
#include <stdio.h>
int main() {
    int a; 
    scanf("%d", &a);
    int *p = &a;
    printf("%p\t%d\n", p, a);
    scanf("%d", &(*p));
    printf("%p\t%d\n", p, a);

    return 0;
}