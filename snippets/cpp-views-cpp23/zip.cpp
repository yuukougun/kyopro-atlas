#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    // --8<-- [start:core]
    // 同じ位置どうしの積の和（長さが違えば短いほうまで）
    long long dot = 0;
    for (auto [x, y] : views::zip(a, b)) dot += x * y;
    // 同じ位置どうしの最大値の列
    long long mx = 0;
    for (long long z : views::zip_transform([](long long x, long long y) { return max(x, y); }, a, b)) mx += z;
    // --8<-- [end:core]
    cout << dot << ' ' << mx << ' ' << ranges::distance(views::zip(a, b)) << '\n';
}
