#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct UnionFind {
    // par[v] < 0 なら v は根で、-par[v] がグループの大きさ。
    // par[v] >= 0 なら par[v] は v の親。
    vector<int> par;
    explicit UnionFind(int n) : par(n, -1) {}

    int find(int v) {
        if (par[v] < 0) return v;
        return par[v] = find(par[v]);  // 経路圧縮：根に直接つなぎ直す
    }

    // 併合したら true、もともと同じグループなら false を返す
    bool merge(int a, int b) {
        int x = find(a), y = find(b);  // 必ず根どうしをつなぐ
        if (x == y) return false;
        if (-par[x] < -par[y]) swap(x, y);  // x を大きい方にする
        par[x] += par[y];  // 大きさを足す（どちらも負の数）
        par[y] = x;        // 小さい方の根を大きい方の根の下へ
        return true;
    }

    bool same(int a, int b) { return find(a) == find(b); }
    int size(int v) { return -par[find(v)]; }
};
// --8<-- [end:core]

int main() {
    // 入力：n q、続く q 行は「0 a b」（併合）・「1 a b」（同じか）・「2 a」（大きさ）。0-indexed
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    int groups = n;  // グループの数 = n − 併合に成功した回数
    for (int i = 0; i < q; i++) {
        int t, a;
        cin >> t >> a;
        assert(0 <= a && a < n);
        if (t == 0) {
            int b;
            cin >> b;
            assert(0 <= b && b < n);
            if (uf.merge(a, b)) groups--;
        } else if (t == 1) {
            int b;
            cin >> b;
            assert(0 <= b && b < n);
            cout << (uf.same(a, b) ? "Yes" : "No") << '\n';
        } else {
            cout << uf.size(a) << '\n';
        }
    }
    int roots = 0;
    for (int v = 0; v < n; v++) {
        if (uf.par[v] < 0) roots++;
    }
    assert(roots == groups);
    cout << groups << '\n';
}
