#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int n;
    scanf("%d", &n);  // -O2 と -D_FORTIFY_SOURCE=2 で「戻り値を無視した」警告が出る（Ubuntu の g++ は自動で足す）
    // --8<-- [end:core]
    printf("%d\n", n);
}
