#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long sum(const vector<int>& a) {
    long long s;  // 初期化していない（-O2 の -Wall で警告される）
    for (int x : a) s += x;
    return s;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << sum(a) << '\n';
}
