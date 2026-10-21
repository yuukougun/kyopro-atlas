#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000;      // 頂点数の上限
bitset<MAXN> reach[MAXN];   // reach[v]：v から到達できる頂点の集合（v 自身を含む）

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> indeg(n, 0);
    for (int e = 0; e < m; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        indeg[v]++;
    }
    // トポロジカル順（Kahn 法）。入力は DAG とする
    vector<int> order;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (int i = 0; i < (int)order.size(); i++)
        for (int w : g[order[i]])
            if (--indeg[w] == 0) order.push_back(w);
    assert((int)order.size() == n);
    // --8<-- [start:core]
    // 逆トポロジカル順なら、v を処理するときには行き先 w の集合が完成している
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        reach[v][v] = 1;
        for (int w : g[v]) reach[v] |= reach[w];  // 和集合なので 2 通りの道があっても重ならない
    }
    // --8<-- [end:core]
    // 確かめ：頂点ごとの素朴な探索で到達数を数える
    for (int s = 0; s < n; s++) {
        vector<bool> seen(n, false);
        vector<int> st = {s};
        seen[s] = true;
        int cnt = 1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int w : g[v])
                if (!seen[w]) seen[w] = true, cnt++, st.push_back(w);
        }
        assert((int)reach[s].count() == cnt);
    }
    for (int v = 0; v < n; v++) cout << reach[v].count() << (v + 1 < n ? ' ' : '\n');
}
