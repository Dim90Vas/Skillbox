#include <stdio.h>
#include <stdlib.h>

#define PROGRAM 2 //выбор программы для компиляции
#define FIB fib(n-1)+fib(n-2)

#if PROGRAM==1 //запуск первой программы
int fib(int n) {
    if (n==0) {
        return 0;
    }
    if (n==1) {
        return 1;
    }
    return FIB;
}

int main() {
    int n=2584, m=0;
    for(int i=0; i<n; i++) {
        if(m < n) {
            m = fib(i);
            printf("%d ", m);
        }
    }
    return 0;
}
//=====================================================================================================================================================
#elif PROGRAM==2 //запуск второй программы
#define M 5 //размер массива
#define N 5
#define RAND rand()%127
#define PX printf("%c ",mass[i][j])
#define FOR1 for(int i=0; i<M; i++)
#define FOR2 for(int j=0; j<N; j++)
//заполнение массива
void generate_mass(int mass[M][N]) {
    FOR1 {
        FOR2 {
            mass[i][j]=RAND;
        }
    }
}
//вывод функции
void printmass(char mass[M][N]) {
    FOR1 {
        FOR2 {
            PX;
        }
        printf("\n");
    }
}
//функция с рекурсией
void rec(int mass[M][N], char mass2[M][N], int x, int n, int m) {
    scanf("%d", &x);
    FOR1 {
        FOR2 {
            if(mass[i][j]==x && mass2[i][j]!='1') {
                mass2[i][j]='1';
            }
        }
    }
    printmass(mass2);
    rec(mass,mass2,x,n,m);
}

int main() {
    int x=0,n=0,m=0;
    int mass[M][N];/*={{1,3,5,8,9},{2,4,6,7,0},{9,7,1,4,2},{0,8,6,3,5},{1,3,5,7,9}};*/
    char mass2[M][N]={{'-','-','-','-','-'},{'-','-','-','-','-'},{'-','-','-','-','-'},{'-','-','-','-','-'},{'-','-','-','-','-'}};
    generate_mass(mass);
    rec(mass,mass2,x,n,m);
    return 0;
}
#endif
