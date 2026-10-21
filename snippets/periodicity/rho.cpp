#include <bits/stdc++.h>
using namespace std;

// 状態 0..n-1、遷移 nxt、各状態の値 val。x_0 = s から K 回進めた状態 x_K と、
// 最初の K 項の和 val[x_0] + ... + val[x_{K-1}] を求める（和は long long に収まると仮定）。
int main() {
    int n, s;
    long long K;
    cin >> n >> s >> K;
    vector<int> nxt(n);
    vector<long long> val(n);
    for (auto& v : nxt) cin >> v;
    for (auto& v : val) cin >> v;

    // --8<-- [start:core]
    vector<long long> first(n, -1);  // first[x] = x を初めて訪れた時刻
    vector<int> order;               // order[t] = x_t（再訪するまで）
    int x = s;
    while (first[x] == -1) {         // 状態は n 種類なので n 回以内に終わる
        first[x] = order.size();
        order.push_back(x);
        x = nxt[x];
    }
    long long mu = first[x];                      // 尾の長さ
    long long lam = (long long)order.size() - mu; // 周期
    vector<long long> pre(order.size() + 1, 0);   // pre[t] = x_0..x_{t-1} の値の和
    for (size_t t = 0; t < order.size(); t++) pre[t + 1] = pre[t] + val[order[t]];

    auto state_at = [&](long long k) -> int {     // x_k
        if (k < mu) return order[k];
        return order[mu + (k - mu) % lam];
    };
    auto sum_first = [&](long long k) -> long long {  // x_0..x_{k-1} の値の和
        if (k <= mu) return pre[k];
        long long q = (k - mu) / lam, r = (k - mu) % lam;
        return pre[mu] + q * (pre[mu + lam] - pre[mu]) + (pre[mu + r] - pre[mu]);
    };
    // --8<-- [end:core]

    assert(mu + lam <= n);
    cout << state_at(K) << ' ' << sum_first(K) << '\n';
}
