// 独立集合型の木 DP：黒どうしが隣り合わない白黒の塗り方の数（mod 10^9+7）
// 入力：N、続く N - 1 行に辺 u v（1-indexed）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // --8<-- [start:core]
    // white[v]・black[v]：v を白・黒に塗ったときの、v の部分木の塗り方の数
    vector<mint> white(n), black(n);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        white[v] = 1;  // 子がなければ 1 通り（空の積）
        black[v] = 1;
        for (int c : g[v]) {
            if (c == p) continue;
            self(self, c, v);              // 先に子を確定させる（帰りがけ順）
            white[v] *= white[c] + black[c];  // v が白なら子は白黒どちらでもよい
            black[v] *= white[c];             // v が黒なら子は白だけ
        }
    };
    dfs(dfs, 0, -1);
    mint ans = white[0] + black[0];
    // --8<-- [end:core]
    // 小さい木では全通りを試して確かめる
    if (n <= 15) {
        int cnt = 0;
        for (int s = 0; s < (1 << n); s++) {
            bool ok = true;
            for (int v = 0; v < n; v++)
                for (int c : g[v])
                    if ((s >> v & 1) && (s >> c & 1)) ok = false;
            if (ok) cnt++;
        }
        assert(ans.val() == cnt);
    }
    cout << ans.val() << '\n';
}
