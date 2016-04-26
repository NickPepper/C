#include <stdio.h>
#include <time.h>
// gcc factorial.c -std=c99 -o factorial_c99 -O3
int zeta(int n) {
    int ret = 0;
    for(int p = 5; p <= n; p*=5) {
        ret += n/p;
    }
    return ret;
}

int main() {
    double start, end;
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        start = clock();
        printf("%d\n", zeta(n));
        end = clock();
        printf("\t(%.6lf секунды)\n", (end-start)/CLOCKS_PER_SEC);
    }
    return 0;
}
