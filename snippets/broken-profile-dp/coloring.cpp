// 取り得る状態だけに番号を付ける：'1'・'2'・'3'・'?' の盤の '?' を 1〜3 で埋め、
// 辺で隣り合うマスの数がすべて異なるようにする方法の数（mod 998244353）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:enumerate]
// 状態：境界の w マスの色を 2 bit ずつ並べた整数（0 はまだ塗っていない）
// マス (i, j) の直前の境界は、k < j ならマス (i, k)、k >= j ならマス (i - 1, k)
int get(int s, int k) { return s >> (2 * k) & 3; }

struct Table {
    vector<vector<int>> states;      // states[j]：列 j を塗る直前に取り得る状態（昇順）
    vector<vector<array<int, 3>>> nxt;  // nxt[j][id][c - 1]：色 c で塗った後の状態の番号（-1 は不可）
};

Table enumerate_states(int w) {
    Table t;
    t.states.assign(w, {});
    t.nxt.assign(w, {});
    // 全部 0 の状態から、たどり着ける状態だけを集める（列ごとに広げる）
    vector<set<int>> seen(w);
    seen[0].insert(0);
    bool changed = true;
    while (changed) {  // 増えなくなるまで回す（状態が増えるのは 2 周目まで）
        changed = false;
        for (int j = 0; j < w; j++) {
            for (int s : vector<int>(seen[j].begin(), seen[j].end())) {
                for (int c = 1; c <= 3; c++) {
                    if (get(s, j) == c || (j > 0 && get(s, j - 1) == c)) continue;
                    int to = (s & ~(3 << (2 * j))) | c << (2 * j);
                    changed |= seen[(j + 1) % w].insert(to).second;
                }
            }
        }
    }
    for (int j = 0; j < w; j++) t.states[j].assign(seen[j].begin(), seen[j].end());
    auto id = [&](int j, int s) {  // 状態 s の、列 j での番号
        auto& v = t.states[j];
        return int(lower_bound(v.begin(), v.end(), s) - v.begin());
    };
    for (int j = 0; j < w; j++) {
        for (int s : t.states[j]) {
            array<int, 3> a{-1, -1, -1};
            for (int c = 1; c <= 3; c++) {
                if (get(s, j) == c || (j > 0 && get(s, j - 1) == c)) continue;
                a[c - 1] = id((j + 1) % w, (s & ~(3 << (2 * j))) | c << (2 * j));
            }
            t.nxt[j].push_back(a);
        }
    }
    return t;
}
// --8<-- [end:enumerate]

// --8<-- [start:dp]
mint count_coloring(vector<string> g) {
    int h = g.size(), w = g[0].size();
    if (w > h) {  // 短い辺を横にする（境界の長さが短い辺になる）
        vector<string> tr(w, string(h, '?'));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) tr[j][i] = g[i][j];
        }
        g = tr;
        swap(h, w);
    }
    Table t = enumerate_states(w);
    vector<mint> dp(t.states[0].size(), 0);
    dp[0] = 1;  // 全部 0 の状態は列 0 の番号 0
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            vector<mint> ndp(t.states[(j + 1) % w].size(), 0);
            for (int k = 0; k < (int)dp.size(); k++) {
                if (dp[k] == 0) continue;
                for (int c = 1; c <= 3; c++) {
                    if (g[i][j] != '?' && g[i][j] - '0' != c) continue;
                    int to = t.nxt[j][k][c - 1];
                    if (to >= 0) ndp[to] += dp[k];
                }
            }
            dp = move(ndp);
        }
    }
    mint ans = 0;
    for (mint x : dp) ans += x;
    return ans;
}
// --8<-- [end:dp]

// 確かめ用：すべての塗り方を試す
long long brute(vector<string>& g, int p) {
    int h = g.size(), w = g[0].size();
    if (p == h * w) return 1;
    int i = p / w, j = p % w;
    char orig = g[i][j];
    long long res = 0;
    for (char c = '1'; c <= '3'; c++) {
        if (orig != '?' && orig != c) continue;
        if (i > 0 && g[i - 1][j] == c) continue;
        if (j > 0 && g[i][j - 1] == c) continue;
        if (i + 1 < h && g[i + 1][j] == c) continue;  // 固定のマスとの比較
        if (j + 1 < w && g[i][j + 1] == c) continue;
        g[i][j] = c;
        res += brute(g, p + 1);
        g[i][j] = orig;
    }
    return res;
}

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& s : g) cin >> s;
    mint ans = count_coloring(g);
    if (h * w <= 12) {
        vector<string> b = g;
        assert(ans.val() == brute(b, 0) % 998244353);
    }
    // 境界の状態の数：w ≥ 2 なら列ごとに 9 × 2^(w - 2) 個以下（1 行目の 0 を含む状態を除く）
    int m = min(h, w);
    if (m >= 2) {
        Table t = enumerate_states(m);
        for (int j = 0; j < m; j++) {
            int full = 0;
            for (int s : t.states[j]) {
                bool has0 = false;
                for (int k = 0; k < m; k++) has0 |= get(s, k) == 0;
                if (!has0) full++;
            }
            assert(full <= 9 * (1 << (m - 2)));
        }
    }
    cout << ans.val() << '\n';
}
