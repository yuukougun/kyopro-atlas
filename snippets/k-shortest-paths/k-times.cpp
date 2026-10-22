#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// s から t へのウォークの長さを短い順に K 個返す（K 個に満たなければあるだけ）。
// 辺の重みは 0 以上。同じ長さでも別のウォークなら別に数える
vector<long long> k_shortest_walks(const vector<vector<pair<int, long long>>>& g,
                                   int s, int t, int k) {
    int n = g.size();
    vector<int> cnt(n, 0);  // 各頂点を取り出した回数
    vector<long long> res;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (cnt[v] == k) continue;  // K 回取り出した頂点はもう使わない
        cnt[v]++;                   // d は v への cnt[v] 番目に短いウォークの長さ
        if (v == t) {
            res.push_back(d);
            if ((int)res.size() == k) break;
        }
        for (auto [to, w] : g[v]) {
            if (cnt[to] < k) pq.push({d + w, to});
        }
    }
    return res;
}
// --8<-- [end:core]

// 確かめ用：長さ limit 以下のウォークをすべてたどる（重みが 1 以上の小さいグラフだけ）
void brute(const vector<vector<pair<int, long long>>>& g, int v, int t, long long d,
           long long limit, vector<long long>& out) {
    if (v == t) out.push_back(d);
    for (auto [to, w] : g[v]) {
        if (d + w <= limit) brute(g, to, t, d + w, limit, out);
    }
}

int main() {
    {  // 閉路のある小さいグラフで全列挙と比べる
        mt19937 rng(1);
        for (int iter = 0; iter < 200; iter++) {
            int n = rng() % 4 + 1, m = rng() % 7;
            vector<vector<pair<int, long long>>> g(n);
            for (int i = 0; i < m; i++) g[rng() % n].push_back({(int)(rng() % n), (long long)(rng() % 3 + 1)});
            int s = rng() % n, t = rng() % n, k = rng() % 8 + 1;
            const long long limit = 12;
            vector<long long> all;
            brute(g, s, t, 0, limit, all);
            sort(all.begin(), all.end());
            vector<long long> got = k_shortest_walks(g, s, t, k);
            for (int i = 0; i < (int)got.size(); i++) {
                if (got[i] <= limit) assert(got[i] == all[i]);
            }
            // 長さ limit 以下のウォークが k 個以上あれば、その範囲は必ず全部返る
            if ((int)all.size() >= k && all[k - 1] <= limit) assert((int)got.size() == k);
            if ((int)got.size() < k) assert(all.size() == got.size());
        }
    }
    int n, m, s, t, k;
    cin >> n >> m >> s >> t >> k;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        g[u].push_back({v, c});
    }
    vector<long long> res = k_shortest_walks(g, s, t, k);
    for (int i = 0; i < k; i++) cout << (i < (int)res.size() ? res[i] : -1) << '\n';
}
