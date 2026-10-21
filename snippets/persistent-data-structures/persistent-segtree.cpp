// 永続セグメント木（経路コピー）：一点の代入・区間和。版のコピーは根の番号を代入するだけ
// 入力：N M Q（長さ M の数列が N 本。最初はすべて 0）、続く Q 行は
//   「0 x y」（数列 x を数列 y の丸ごとのコピーにする）
//   「1 x p v」（数列 x の p 番目を v にする）
//   「2 x l r」（数列 x の [l, r) の和を出力する）。添字はすべて 0-indexed
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct PersistentSegTree {
    int m;                      // 列の長さ（葉の区間は [0, m)）
    vector<int> lc, rc;         // 子の番号
    vector<long long> sum;      // 区間の和
    // ノード 0 は「すべて 0 の木」：子が自分自身で和が 0。どの長さの区間にも使い回せる
    PersistentSegTree(int m, int reserve_nodes = 0) : m(m), lc{0}, rc{0}, sum{0} {
        lc.reserve(reserve_nodes); rc.reserve(reserve_nodes); sum.reserve(reserve_nodes);
    }
    int make(int l, int r, long long s) {  // 新しいノードを作って番号を返す
        lc.push_back(l); rc.push_back(r); sum.push_back(s);
        return (int)sum.size() - 1;
    }
    // 版 t の p 番目を v にした新しい版の根を返す（t は書き換えない）
    int set(int t, int p, long long v) { return set(t, 0, m, p, v); }
    int set(int t, int kl, int kr, int p, long long v) {
        if (kr - kl == 1) return make(0, 0, v);
        int mid = (kl + kr) / 2;
        int l = lc[t], r = rc[t];  // 先に読む（make の push_back で参照が無効になるので）
        if (p < mid) l = set(l, kl, mid, p, v);
        else r = set(r, mid, kr, p, v);
        return make(l, r, sum[l] + sum[r]);
    }
    long long prod(int t, int l, int r) const { return prod(t, 0, m, l, r); }
    long long prod(int t, int kl, int kr, int l, int r) const {
        if (r <= kl || kr <= l || t == 0) return 0;
        if (l <= kl && kr <= r) return sum[t];
        int mid = (kl + kr) / 2;
        return prod(lc[t], kl, mid, l, r) + prod(rc[t], mid, kr, l, r);
    }
};
// --8<-- [end:core]

int main() {
    // 小さい乱択で素朴な方法と比べる
    {
        mt19937 rng(1);
        for (int iter = 0; iter < 200; iter++) {
            int n = rng() % 4 + 1, m = rng() % 7 + 1;
            PersistentSegTree st(m);
            vector<int> root(n, 0);
            vector<vector<long long>> naive(n, vector<long long>(m, 0));
            for (int t = 0; t < 50; t++) {
                int type = rng() % 3, x = rng() % n;
                if (type == 0) {
                    int y = rng() % n;
                    root[x] = root[y];
                    naive[x] = naive[y];
                } else if (type == 1) {
                    int p = rng() % m;
                    long long v = (long long)(rng() % 21) - 10;
                    root[x] = st.set(root[x], p, v);
                    naive[x][p] = v;
                } else {
                    int l = rng() % (m + 1), r = rng() % (m + 1);
                    if (l > r) swap(l, r);
                    long long s = 0;
                    for (int i = l; i < r; i++) s += naive[x][i];
                    assert(st.prod(root[x], l, r) == s);
                }
            }
        }
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    // --8<-- [start:main]
    // 1 回の set で作るノードは高さ + 1 個（m = 2×10^5 なら 19 個）
    PersistentSegTree st(m, 1 + q * (__lg(max(m - 1, 1)) + 2));
    vector<int> root(n, 0);  // 数列 x の今の版の根。最初はすべて 0 の木
    // --8<-- [end:main]
    for (int i = 0; i < q; i++) {
        int type, x;
        cin >> type >> x;
        if (type == 0) {
            int y;
            cin >> y;
            root[x] = root[y];  // 丸ごとのコピーは根の指し替え
        } else if (type == 1) {
            int p;
            long long v;
            cin >> p >> v;
            root[x] = st.set(root[x], p, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.prod(root[x], l, r) << '\n';
        }
    }
}
