#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    long long f0 = 0, f1 = 1;
    for (int i = 0; i < n; i++) tie(f0, f1) = pair{f1, f0 + f1};  // 右辺を先に作ってから代入
    cout << f0 << '\n';  // フィボナッチ数 F(n)

    int cur = 10;
    int prev = exchange(cur, 20);  // cur に 20 を入れ、前の値 10 を返す
    cout << prev << ' ' << cur << '\n';  // 10 20
    // --8<-- [end:core]
}
