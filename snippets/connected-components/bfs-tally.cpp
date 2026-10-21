#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> eu(m), ev(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        eu[i]--, ev[i]--;  // 1-indexed → 0-indexed
        g[eu[i]].push_back(ev[i]);
        g[ev[i]].push_back(eu[i]);
    }
    // --8<-- [start:core]
    // comp[v] = 頂点 v の成分の番号（-1 は未訪問）
    vector<int> comp(n, -1);
    int c = 0;  // 成分の数
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        comp[s] = c;  // 印は push のときに付ける
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (comp[to] == -1) {
                    comp[to] = c;
                    q.push(to);
                }
            }
        }
        c++;
    }
    // 成分ごとの頂点数と辺数（辺は辺リストから 1 本ずつ数える）
    vector<int> vcnt(c, 0), ecnt(c, 0);
    for (int v = 0; v < n; v++) vcnt[comp[v]]++;
    for (int i = 0; i < m; i++) ecnt[comp[eu[i]]]++;  // 自己ループ・多重辺も 1 本ずつ
    // --8<-- [end:core]
    assert(accumulate(vcnt.begin(), vcnt.end(), 0) == n);
    assert(accumulate(ecnt.begin(), ecnt.end(), 0) == m);
    int mx = 0, tree = 0, namori = 0, other = 0;
    for (int k = 0; k < c; k++) {
        mx = max(mx, vcnt[k]);
        if (ecnt[k] == vcnt[k] - 1) tree++;
        else if (ecnt[k] == vcnt[k]) namori++;
        else other++;
    }
    // 成分の数・最大の頂点数・木の数・なもりの数・閉路が 2 つ以上の数
    cout << c << ' ' << mx << ' ' << tree << ' ' << namori << ' ' << other << '\n';
}
