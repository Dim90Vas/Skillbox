#include <stdio.h>
#include <stdlib.h>

void counter(void) {
    int ch=9;
        while(ch>=0) {
            printf("%d\n",ch);
            ch--;
        }
}
void tablePif(void) {
    for(int i=1; i<=10; ++i) {
        for(int j=1; j<=10; ++j) {
            printf("%d\t",i*j);
        }
        printf("\n\n");
    }
}
void sortnum(int mass[], int m) { //Нахождение минимального числа в массиве
    int min_ch=9999;
    int newmass[m];
    int n=m;
    while(n>0) {
    for(int i=0; i<m; ++i) {
        if(mass[i]<min_ch) {
            min_ch=mass[i];
        }
    }
    for(int j=0; j<m; ++j) {
        if(mass[j]==min_ch) {
            mass[j]=9999;
        }
    }
    newmass[m-n]=min_ch;
    min_ch=9999;
    --n;
    }
    for(int i=0; i<m; ++i) {
        printf("%d ",newmass[i]);
    }
    printf("\n");
}

int main() {
    int number, x=1;
    int m=5;//Размер массива
    int mass[m];
    while(x!=0) {
        printf("Please enter command: ");
        scanf("%d",&number);
        switch(number) {
            case 1:
                counter();
                break;
            case 2:
                tablePif();
                break;
            case 3:
                printf("Enter numbers separated by spaces: \n");
                for(int i=0; i<m; ++i) {
                    scanf("%d",&mass[i]);
                }
                for(int j=0; j<m; ++j) {
                    printf("%d ",mass[j]);
                }
                printf("\n");
                sortnum(mass, m);
                break;
            case 4: x=0;
                break;
            default: printf("Please enter command from 1 to 3, or 4 to exit\n");
                break;
        }
    }
    return 0;
}
