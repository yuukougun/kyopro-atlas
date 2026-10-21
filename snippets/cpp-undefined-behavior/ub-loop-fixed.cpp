#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    // --8<-- [start:core]
    int cnt = 0;
    for (long long i = x; 0 < i && i <= INT_MAX; i *= 2) cnt++;  // 広い型で計算し、範囲を条件で確かめる
    cout << cnt << '\n';
    // --8<-- [end:core]
}
