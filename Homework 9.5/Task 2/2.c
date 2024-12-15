#include <stdio.h>
#include <stdlib.h>
#define M 5 //размер массива
#define N 5
//заполнение массива
void generate_mass(int mass[M][N]) {
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            mass[i][j]=rand()%127;
        }
    }
}
//вывод функции
void printmass(char mass[M][N]) {
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            printf("%c ",mass[i][j]);
        }
        printf("\n");
    }
}
//функция с рекурсией
void rec(int mass[M][N], char mass2[M][N], int x, int n, int m) {
    scanf("%d", &x);
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
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
