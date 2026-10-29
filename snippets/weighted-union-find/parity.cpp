// 偶奇の Union-Find（差を XOR にする）で、辺を足すたびに 2 色に塗れるかを答える
// 入力：N M、続く M 行は「u v」（u と v を違う色にする）。各辺の後に Yes（塗れる）か No を出力
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct ParityUnionFind {
    vector<int> par;  // 根なら −(成分の大きさ)
    vector<int> col;  // col[v] = (v の色) XOR (親の色)。圧縮の後は根との XOR
    explicit ParityUnionFind(int n) : par(n, -1), col(n, 0) {}
    int find(int v) {
        if (par[v] < 0) return v;
        int r = find(par[v]);
        col[v] ^= col[par[v]];  // 加算の代わりに XOR で足す
        par[v] = r;
        return r;
    }
    // (u の色) XOR (v の色) = w を加える。w = 1 なら違う色、0 なら同じ色
    bool merge(int u, int v, int w) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return (col[u] ^ col[v]) == w;
        w ^= col[u] ^ col[v];  // 根どうしの XOR に直す（XOR では符号の反転が要らない）
        if (-par[ru] < -par[rv]) swap(ru, rv);
        par[ru] += par[rv];
        par[rv] = ru;
        col[rv] = w;
        return true;
    }
};
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    ParityUnionFind uf(n);
    bool bipartite = true;  // 一度塗れなくなったら、辺を足しても戻らない
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (!uf.merge(u, v, 1)) bipartite = false;
        cout << (bipartite ? "Yes" : "No") << '\n';
    }
    // 長さ 4 の閉路は塗れ、長さ 3 の閉路は塗れないことを確かめる
    ParityUnionFind a(4), b(3);
    assert(a.merge(0, 1, 1) && a.merge(1, 2, 1) && a.merge(2, 3, 1) && a.merge(3, 0, 1));
    assert(b.merge(0, 1, 1) && b.merge(1, 2, 1) && !b.merge(2, 0, 1));
}
