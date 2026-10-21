#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<int> f(n);
    vector<long long> w(n);  // 状態 v にいるときに得る値
    for (int v = 0; v < n; v++) cin >> f[v];
    for (int v = 0; v < n; v++) cin >> w[v];

    // --8<-- [start:core]
    // K < 2^40（≒ 1.1 × 10^12）、w ≤ 10^6 を想定。段を K の上限に合わせると、
    // 使わない上の段の和（最大 2^39 × 10^6 ≒ 5.5 × 10^17）もあふれない
    const int LOG = 40;
    vector<vector<int>> nxt(LOG, vector<int>(n));
    // sum[k][v]：v から 2^k 回進む間にいた状態（時刻 0, 1, …, 2^k − 1）の w の和。
    // 着いた先（時刻 2^k）は含めない半開の持ち方
    vector<vector<long long>> sum(LOG, vector<long long>(n));
    nxt[0] = f;
    sum[0] = w;
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) {
            int mid = nxt[k][v];
            nxt[k + 1][v] = nxt[k][mid];
            sum[k + 1][v] = sum[k][v] + sum[k][mid];  // 前半 [0, 2^k) と後半 [2^k, 2^(k+1))
        }
    }
    // 0 から K 回進む：通った K 個の状態の w の和と、着いた先
    int v = 0;
    long long total = 0;
    for (int k = 0; k < LOG; k++) {
        if (K >> k & 1) {
            total += sum[k][v];  // v を含み、跳んだ先を含まない
            v = nxt[k][v];
        }
    }
    // --8<-- [end:core]

    if (K <= 1000) {  // 素朴なシミュレーションと比べる
        int u = 0;
        long long s = 0;
        for (long long t = 0; t < K; t++) {
            s += w[u];
            u = f[u];
        }
        assert(u == v && s == total);
    }
    cout << v << ' ' << total << '\n';
}
