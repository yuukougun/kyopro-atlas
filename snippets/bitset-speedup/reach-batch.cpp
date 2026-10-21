#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    vector<int> indeg(n, 0);
    for (int e = 0; e < m; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        indeg[v]++;
    }
    vector<int> qa(q), qb(q);
    for (int k = 0; k < q; k++) {
        cin >> qa[k] >> qb[k];
        qa[k]--, qb[k]--;
    }
    vector<int> order;  // トポロジカル順（Kahn 法）。入力は DAG とする
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (int i = 0; i < (int)order.size(); i++)
        for (int w : g[order[i]])
            if (--indeg[w] == 0) order.push_back(w);
    assert((int)order.size() == n);
    vector<bool> ans(q);
    // --8<-- [start:core]
    // クエリを 64 個ずつまとめる。mask[v] の bit k：その組の k 番目のクエリの始点から v へ届くか
    vector<unsigned long long> mask(n);
    for (int base = 0; base < q; base += 64) {
        int cnt = min(64, q - base);
        fill(mask.begin(), mask.end(), 0ULL);
        for (int k = 0; k < cnt; k++) mask[qa[base + k]] |= 1ULL << k;
        for (int v : order)                          // トポロジカル順に前へ流す
            for (int w : g[v]) mask[w] |= mask[v];   // 64 個のクエリを 1 回の OR で進める
        for (int k = 0; k < cnt; k++) ans[base + k] = (mask[qb[base + k]] >> k) & 1;
    }
    // --8<-- [end:core]
    // 確かめ：クエリごとの素朴な探索
    for (int k = 0; k < q; k++) {
        vector<bool> seen(n, false);
        vector<int> st = {qa[k]};
        seen[qa[k]] = true;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int w : g[v])
                if (!seen[w]) seen[w] = true, st.push_back(w);
        }
        assert(seen[qb[k]] == ans[k]);
    }
    for (int k = 0; k < q; k++) cout << (ans[k] ? "Yes" : "No") << '\n';
}
