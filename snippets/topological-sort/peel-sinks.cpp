// 出次数 0 の頂点を逆辺で剥がしていき、残った頂点（無限に歩き続けられる頂点）を数える。
// N 頂点 M 辺の有向グラフ（入力は 1-indexed）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n >= 1 && m >= 0);
    vector<vector<int>> rg(n);  // 逆辺：rg[v] は v へ入る辺の始点
    vector<int> outdeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        assert(0 <= a && a < n && 0 <= b && b < n);
        rg[b].push_back(a);
        outdeg[a]++;
    }

    // --8<-- [start:core]
    // 出次数 0 の頂点（行き止まり）から剥がす。剥がした頂点からの歩みは必ず止まる
    queue<int> q;
    vector<bool> removed(n, false);
    for (int v = 0; v < n; v++) if (outdeg[v] == 0) q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        removed[v] = true;
        for (int u : rg[v]) {
            if (--outdeg[u] == 0) q.push(u);  // u の行き先がすべて剥がれた
        }
    }
    int alive = 0;  // 残った頂点からは、残った頂点へ必ず進める
    for (int v = 0; v < n; v++) if (!removed[v]) alive++;
    // --8<-- [end:core]

    cout << alive << '\n';
}
