#include <bits/stdc++.h>
using namespace std;

template <class T, class U>
bool chmin(T& a, const U& b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    // --8<-- [start:core]
    int a = 1;
    long long b = -(1LL << 32) + 5;  // int に入らない値
    chmin(a, b);                     // b < a なので a = b。int に入らず、上位が切り捨てられる
    cout << a << '\n';               // 手元では 5（-Wall -Wextra でも警告は出ない）
    // --8<-- [end:core]
}
