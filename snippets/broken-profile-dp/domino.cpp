// 1 マスずつ進める：H×W の盤の空きマス（'.'）を 1×2 のドミノでちょうど覆う方法の数（mod 998244353）
// '#' のマスには置けない。幅 W が小さい（W ≤ 16 程度）ことを使う
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint count_domino(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    // マス (i, j) を処理する直前の状態 S の bit k：
    //   k < j なら マス (i + 1, k)、k >= j なら マス (i, k) が、すでに覆われているか
    vector<mint> dp(1 << w, 0), ndp(1 << w);
    dp[0] = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fill(ndp.begin(), ndp.end(), 0);
            for (int S = 0; S < (1 << w); S++) {
                if (dp[S] == 0) continue;
                int T = S & ~(1 << j);  // bit j はこの後マス (i + 1, j) を表す
                if ((S >> j & 1) || g[i][j] == '#') {
                    // すでに覆われている（か置けない）ので何もしない
                    // 置けないマスが上から覆われることはない（縦に置くときに確かめる）
                    ndp[T] += dp[S];
                    continue;
                }
                // 縦に置く：マス (i + 1, j) を覆う
                if (i + 1 < h && g[i + 1][j] == '.') ndp[T | 1 << j] += dp[S];
                // 横に置く：マス (i, j + 1) を覆う（bit j + 1 はまだ行 i を表す）
                if (j + 1 < w && g[i][j + 1] == '.' && !(S >> (j + 1) & 1)) {
                    ndp[T | 1 << (j + 1)] += dp[S];
                }
            }
            swap(dp, ndp);
        }
    }
    return dp[0];  // 盤の外（行 h）にはみ出していない
}
// --8<-- [end:core]

// 確かめ用：左上から順に、最初の空きマスを縦か横のドミノで覆う全探索
long long brute(vector<string>& g) {
    int h = g.size(), w = g[0].size();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (g[i][j] != '.') continue;
            long long res = 0;
            g[i][j] = 'x';
            if (i + 1 < h && g[i + 1][j] == '.') {
                g[i + 1][j] = 'x';
                res += brute(g);
                g[i + 1][j] = '.';
            }
            if (j + 1 < w && g[i][j + 1] == '.') {
                g[i][j + 1] = 'x';
                res += brute(g);
                g[i][j + 1] = '.';
            }
            g[i][j] = '.';
            return res;
        }
    }
    return 1;
}

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& s : g) cin >> s;
    mint ans = count_domino(g);
    if (h * w <= 30) {
        vector<string> t = g;
        assert(ans.val() == brute(t) % 998244353);
    }
    cout << ans.val() << '\n';
}
