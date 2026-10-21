// Union-Find の代表元に「値ごとの個数」の map を持たせる（ACL の dsu）
// 入力：N Q、C_0 … C_{N-1}（頂点 i の色）、続く Q 行は「1 a b」（a と b の成分を併合）か「2 x y」（x の成分にいる色 y の頂点数を出力）
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// cnt[r] は、r が代表元のときだけ「r の成分にいる色ごとの頂点数」として正しい
void unite(atcoder::dsu& d, vector<map<int, int>>& cnt, int a, int b) {
    int ra = d.leader(a), rb = d.leader(b);   // merge の前に両方の代表元を取っておく
    if (ra == rb) return;
    int r = d.merge(a, b);                    // サイズの大きい方が代表元に残る
    int other = (r == ra ? rb : ra);          // 代表元でなくなった方（サイズは小さい方）
    if (cnt[other].size() > cnt[r].size()) swap(cnt[other], cnt[r]);
    for (auto [color, k] : cnt[other]) cnt[r][color] += k;
    cnt[other].clear();
}

int count_color(atcoder::dsu& d, vector<map<int, int>>& cnt, int x, int y) {
    auto& m = cnt[d.leader(x)];
    auto it = m.find(y);                      // m[y] と書くと、ない色の項目が増える
    return it == m.end() ? 0 : it->second;
}
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    atcoder::dsu d(n);
    vector<map<int, int>> cnt(n);
    for (int i = 0; i < n; i++) cnt[i][c[i]] = 1;
    vector<int> group(n);  // 素朴な方法：成分の番号を全部書き換える
    iota(group.begin(), group.end(), 0);
    for (int i = 0; i < q; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            unite(d, cnt, a, b);
            int ga = group[a], gb = group[b];
            for (int v = 0; v < n; v++) if (group[v] == ga) group[v] = gb;
        } else {
            int res = count_color(d, cnt, a, b);
            int expected = 0;
            for (int v = 0; v < n; v++) if (group[v] == group[a] && c[v] == b) expected++;
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
