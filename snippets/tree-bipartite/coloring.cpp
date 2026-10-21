#include <bits/stdc++.h>
using namespace std;

// 頂点 u から各頂点までの距離（重みの和）を素朴に求める。assert での照合用
vector<long long> naive_dist(const vector<vector<pair<int, int>>>& g, int u) {
    int n = g.size();
    vector<long long> d(n, -1);
    d[u] = 0;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [c, w] : g[v]) {
            if (d[c] == -1) {
                d[c] = d[v] + w;
                q.push(c);
            }
        }
    }
    return d;
}

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);  // (隣の頂点, 辺の重み)
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // --8<-- [start:core]
    // color[v] = 根 0 から v までの重みの和の偶奇（重みがすべて 1 なら深さの偶奇）
    vector<int> color(n, -1);
    color[0] = 0;
    queue<int> q;  // 再帰を使わない BFS（パス状の木でも深くならない）
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [c, w] : g[v]) {
            if (color[c] != -1) continue;  // 木なので塗った隣は親だけ
            color[c] = color[v] ^ (w % 2);  // 奇数の辺だけ色を入れ替える
            q.push(c);
        }
    }
    long long a = count(color.begin(), color.end(), 0);
    long long b = n - a;
    // 距離が奇数の頂点の組 = 色の違う組 = a * b（long long で掛ける）
    long long odd_pairs = a * b;
    // --8<-- [end:core]

    cout << a << ' ' << b << '\n' << odd_pairs << '\n';

    int qn;
    cin >> qn;
    for (int i = 0; i < qn; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        // 距離 d(u, v) の偶奇は、色が同じなら偶数、違えば奇数
        bool odd = color[u] != color[v];
        assert(odd == (naive_dist(g, u)[v] % 2 == 1));
        cout << (odd ? "Odd" : "Even") << '\n';
    }

    if (n <= 200) {  // 小さい木では、距離が奇数の組を全部数えて照合する
        long long cnt = 0;
        for (int u = 0; u < n; u++) {
            auto d = naive_dist(g, u);
            for (int v = u + 1; v < n; v++) cnt += d[v] % 2;
        }
        assert(cnt == odd_pairs);
    }
}
