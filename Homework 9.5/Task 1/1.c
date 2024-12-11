#include <stdio.h>
int fib(int n) {
    if (n==0) {
        return 0;
    }
    if (n==1) {
        return 1;
    }
    return fib(n-1)+fib(n-2);
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
