// N 個の整数から、和がちょうど X になる選び方（空集合を含む）の個数を bit 全探索で数える
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_subsets(const vector<long long>& a, long long x) {
    int n = a.size();
    long long cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {   // mask = 0 は空集合
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) sum += a[i];       // i ビット目が 1 なら要素 i を選ぶ
        }
        if (sum == x) cnt++;
    }
    return cnt;
}
// --8<-- [end:core]

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    assert(n <= 20);
    cout << count_subsets(a, x) << '\n';
}
