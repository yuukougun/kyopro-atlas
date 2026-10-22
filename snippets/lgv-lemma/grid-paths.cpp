// LGV 補題：格子上の k 本の経路（右 +x・上 +y の 1 歩ずつ）について、
// det M（M[i][j] = 始点 a_i から終点 b_j への経路数）を mod 998244353 で求める。
// 座標が小さければ、経路の組を全列挙した符号付きの和と一致することを assert で確かめる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:det]
// 掃き出し法で行列式を求める（mod 素数）。行を交換するたびに符号を反転する
mint det(vector<vector<mint>> m) {
    int k = m.size();
    mint res = 1;
    for (int c = 0; c < k; c++) {
        int p = c;
        while (p < k && m[p][c] == 0) p++;
        if (p == k) return 0;
        if (p != c) {
            swap(m[p], m[c]);
            res = -res;
        }
        res *= m[c][c];
        mint inv = m[c][c].inv();
        for (int r = c + 1; r < k; r++) {
            mint f = m[r][c] * inv;
            for (int j = c; j < k; j++) m[r][j] -= f * m[c][j];
        }
    }
    return res;
}
// --8<-- [end:det]

long long binom_small(int n, int r) {
    if (r < 0 || r > n) return 0;
    long long v = 1;
    for (int i = 1; i <= r; i++) v = v * (n - r + i) / i;
    return v;
}

// --8<-- [start:lgv]
// 右か上に 1 歩ずつ進む格子路の数：dx・dy のどちらかが負なら 0
mint paths(pair<int, int> s, pair<int, int> t) {
    int dx = t.first - s.first, dy = t.second - s.second;
    if (dx < 0 || dy < 0) return 0;
    // 座標が小さいときだけ使える素朴な計算（大きいと long long があふれる）。
    // 座標が大きいときは階乗の表（binomial-precompute）の二項係数に替える
    return binom_small(dx + dy, dx);
}

// 頂点を共有しない経路の組（a_i → b_σ(i)）の、sgn(σ) を掛けた個数の和
mint lgv(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
    int k = a.size();
    vector<vector<mint>> m(k, vector<mint>(k));
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) m[i][j] = paths(a[i], b[j]);
    return det(m);
}
// --8<-- [end:lgv]

// 全列挙：s から t への経路（通る点の列）をすべて作る
void all_paths(pair<int, int> s, pair<int, int> t, vector<pair<int, int>>& cur,
               vector<vector<pair<int, int>>>& out) {
    cur.push_back(s);
    if (s == t) {
        out.push_back(cur);
    } else {
        if (s.first < t.first) all_paths({s.first + 1, s.second}, t, cur, out);
        if (s.second < t.second) all_paths({s.first, s.second + 1}, t, cur, out);
    }
    cur.pop_back();
}

long long brute(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
    int k = a.size();
    vector<int> perm(k);
    iota(perm.begin(), perm.end(), 0);
    long long total = 0;
    do {
        int inv = 0;
        for (int i = 0; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (perm[i] > perm[j]) inv++;
        vector<vector<vector<pair<int, int>>>> ps(k);
        bool ok = true;
        for (int i = 0; i < k; i++) {
            vector<pair<int, int>> cur;
            all_paths(a[i], b[perm[i]], cur, ps[i]);
            if (ps[i].empty()) ok = false;
        }
        if (!ok) continue;
        long long cnt = 0;
        vector<int> idx(k, 0);
        while (true) {
            set<pair<int, int>> used;
            size_t len = 0;
            for (int i = 0; i < k; i++) {
                for (auto& v : ps[i][idx[i]]) used.insert(v);
                len += ps[i][idx[i]].size();
            }
            if (used.size() == len) cnt++;  // どの 2 本も頂点を共有しない
            int i = 0;
            while (i < k && ++idx[i] == (int)ps[i].size()) idx[i++] = 0;
            if (i == k) break;
        }
        total += (inv % 2 == 0 ? cnt : -cnt);
    } while (next_permutation(perm.begin(), perm.end()));
    return total;
}

int main() {
    int k;
    cin >> k;
    vector<pair<int, int>> a(k), b(k);
    for (auto& [x, y] : a) cin >> x >> y;
    for (auto& [x, y] : b) cin >> x >> y;
    mint ans = lgv(a, b);
    bool small = k <= 3;
    for (int i = 0; i < k; i++)
        small = small && max({a[i].first, a[i].second, b[i].first, b[i].second}) <= 4;
    if (small) assert(ans == mint(brute(a, b)));
    cout << ans.val() << '\n';
}
