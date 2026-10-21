#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int n;
    long long m;
    if (scanf("%d %lld", &n, &m) != 2) return 1;  // 変数のアドレス（&）を渡す。戻り値は読めた個数
    double x = (double)m / n;
    printf("%d %lld\n", n, m);         // int は %d、long long は %lld
    printf("%.10f\n", x);              // 小数点以下 10 桁
    printf("%5d|%-5d|%05d\n", n, n, n);  // 幅 5（右寄せ）・左寄せ・0 埋め
    // --8<-- [end:core]
}
