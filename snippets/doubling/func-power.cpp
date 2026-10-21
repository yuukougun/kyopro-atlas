#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<int> x(n);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> x[i];  // 0-indexed
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    // 1 回の操作 B[i] = A[x[i]] を K 回行う。
    // K 回後の B[i] は A[x^K(i)]（x^K は x を K 回合成した写像）
    vector<int> res(n), p = x;  // res = x^(処理済みの桁)、p = x^(2^k)
    iota(res.begin(), res.end(), 0);  // 0 回の合成は恒等写像
    while (K > 0) {
        if (K & 1) {
            for (int i = 0; i < n; i++) res[i] = p[res[i]];
        }
        vector<int> q(n);
        for (int i = 0; i < n; i++) q[i] = p[p[i]];  // 2^k 回 → 2^(k+1) 回
        p = q;
        K >>= 1;
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) cout << a[res[i]] << (i + 1 < n ? ' ' : '\n');
}
