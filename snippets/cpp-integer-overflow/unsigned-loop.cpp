#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    // 隣り合う 2 つを比べる。v が空でも 1 回も回らない
    for (int i = 0; i + 1 < ssize(v); i++) cout << (v[i] < v[i + 1]);
    cout << '\n';
    // 逆順のループは int で回す（size_t i で i >= 0 と書くと終わらない）
    for (int i = ssize(v) - 1; i >= 0; i--) cout << v[i] << ' ';
    // --8<-- [end:core]
    cout << '\n';
}
