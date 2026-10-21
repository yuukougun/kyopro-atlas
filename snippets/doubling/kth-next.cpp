#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> f(n);  // v の次の状態は f[v]（0-indexed）
    for (int v = 0; v < n; v++) cin >> f[v];

    // --8<-- [start:core]
    const int LOG = 60;  // K < 2^60（10^18 < 2^60 ≒ 1.15 × 10^18）
    // nxt[k][v]：v から 2^k 回進んだ先
    vector<vector<int>> nxt(LOG, vector<int>(n));
    nxt[0] = f;
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) {
            nxt[k + 1][v] = nxt[k][nxt[k][v]];  // 2^k 回進んでから、さらに 2^k 回
        }
    }
    // v から K 回進んだ先：K の 2 進表記で 1 の桁だけ跳ぶ
    auto jump = [&](int v, long long K) {
        for (int k = 0; k < LOG; k++) {
            if (K >> k & 1) v = nxt[k][v];
        }
        return v;
    };
    // --8<-- [end:core]

    while (q--) {
        int v;
        long long K;
        cin >> v >> K;
        int ans = jump(v, K);
        if (K <= 1000) {  // 小さい K は素朴なシミュレーションと比べる
            int u = v;
            for (long long t = 0; t < K; t++) u = f[u];
            assert(u == ans);
        }
        cout << ans << '\n';
    }
}
