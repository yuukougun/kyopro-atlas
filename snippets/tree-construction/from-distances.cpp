// 距離の表から木を作る：全点対の距離 D（対角は 0、ほかは正）を実現する重み付きの木があるかを判定する。
// 距離の短い順に閉路を作らない組を辺に選び（クラスカル法）、作った木の距離を全点から測って D と比べる。
// 入力：N、続く N 行に D の各行（N × N）。出力：Yes か No
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> d(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> d[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) assert(i == j ? d[i][j] == 0 : d[i][j] > 0);

    // --8<-- [start:core]
    // 1. 候補の辺：すべての組 (i, j) を距離の短い順に並べる
    vector<tuple<long long, int, int>> cand;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) cand.emplace_back(d[i][j], i, j);
    sort(cand.begin(), cand.end());

    // 2. 閉路を作らない組だけを辺にする（木があるなら、これがその木になる）
    atcoder::dsu uf(n);
    vector<vector<pair<int, long long>>> g(n);
    for (auto [w, i, j] : cand) {
        if (uf.same(i, j)) continue;
        uf.merge(i, j);
        g[i].emplace_back(j, w);
        g[j].emplace_back(i, w);
    }

    // 3. 確かめる：作った木の距離を全点から測り、D とすべて一致するか
    bool ok = true;
    for (int s = 0; s < n && ok; s++) {
        vector<long long> dist(n, -1);
        dist[s] = 0;
        vector<int> st = {s};  // 再帰を使わない（パス状の木でも深くならない）
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (auto [u, w] : g[v]) {
                if (dist[u] != -1) continue;
                dist[u] = dist[v] + w;
                st.push_back(u);
            }
        }
        for (int t = 0; t < n; t++)
            if (dist[t] != d[s][t]) ok = false;
    }
    // --8<-- [end:core]

    cout << (ok ? "Yes" : "No") << '\n';
}
