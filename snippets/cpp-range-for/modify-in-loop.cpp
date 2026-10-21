#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:bad]
    // for (int x : v) if (x % 2 == 0) v.push_back(x / 2);  // 未定義動作：範囲 for が覚えた位置が無効になる
    // --8<-- [end:bad]
    // --8<-- [start:core]
    int m = v.size();               // 回す前の長さを覚える
    for (int i = 0; i < m; i++) {   // 添字で回す。v[i] は毎回引き直す
        if (v[i] % 2 == 0) v.push_back(v[i] / 2);
    }
    // --8<-- [end:core]
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << (i + 1 < (int)v.size() ? " " : "");
    cout << '\n';
}
