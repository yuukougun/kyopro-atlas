#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    // --8<-- [start:core]
    // a は昇順。a[i] >= x を満たす最初の i を求める
    auto check = [&](int i) { return a[i] >= x; };
    int ng = -1, ok = n;  // 番兵：check(-1) は偽、check(n) は真とみなし、呼ばない
    while (abs(ok - ng) > 1) {
        int mid = ng + (ok - ng) / 2;  // ng < mid < ok なので a[mid] は範囲内
        if (check(mid)) ok = mid;
        else ng = mid;
    }
    // ここで ok - ng = 1。ok は条件を満たす最初の位置（なければ n）
    // --8<-- [end:core]
    assert(ok == lower_bound(a.begin(), a.end(), x) - a.begin());
    cout << ok << '\n';
}
