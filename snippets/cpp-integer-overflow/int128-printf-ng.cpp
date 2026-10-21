#include <bits/stdc++.h>
using namespace std;

int main() {
    // printf の %lld に __int128 を渡す（本文には取り込まない）
    __int128 x = (__int128)1 << 100;
    printf("%lld\n", x);  // 警告 -Wformat=。手元では 0
}
