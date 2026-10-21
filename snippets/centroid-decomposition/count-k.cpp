// 距離がちょうど K（K ≥ 1）の頂点の組 {u, v} の個数を重心分解で数える。
// 入力：N K、続く N-1 行に辺 a b（1-indexed）。出力：組の個数。
// main の最初で、小さな乱数の木について素朴な BFS の答えと照らし合わせる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:centroid]
// r を含む成分（removed でない頂点の連結成分）の重心を返す。
// 再帰を使わず、BFS の順を逆にたどって部分木サイズを求める（パス状の木でも深くならない）。
int find_centroid(int r, const vector<vector<int>>& g, const vector<char>& removed,
                  vector<int>& sz, vector<int>& par) {
    vector<int> order = {r};
    par[r] = -1;
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int to : g[v]) {
            if (to == par[v] || removed[to]) continue;
            par[to] = v;
            order.push_back(to);
        }
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        sz[v] = 1;
        for (int to : g[v]) {
            if (to != par[v] && !removed[to]) sz[v] += sz[to];
        }
    }
    int total = order.size();
    int v = r;
    while (true) {  // 半分を超える子があれば、そちらへ進む
        int next = -1;
        for (int to : g[v]) {
            if (to != par[v] && !removed[to] && sz[to] * 2 > total) next = to;
        }
        if (next == -1) return v;
        v = next;
    }
}
// --8<-- [end:centroid]

// --8<-- [start:core]
long long count_pairs_k(int n, const vector<vector<int>>& g, int k) {
    vector<char> removed(n, 0);
    vector<int> sz(n), par(n), dep(n);
    long long ans = 0;

    // s から、removed でない頂点を BFS し、距離 d の頂点の数 cnt[d] を返す（距離の初期値 d0）
    auto depth_count = [&](int s, int p, int d0) {
        vector<int> cnt;
        vector<pair<int, int>> q = {{s, p}};
        dep[s] = d0;
        for (int i = 0; i < (int)q.size(); i++) {
            auto [v, pv] = q[i];
            if ((int)cnt.size() <= dep[v]) cnt.resize(dep[v] + 1, 0);
            cnt[dep[v]]++;
            for (int to : g[v]) {
                if (to == pv || removed[to]) continue;
                dep[to] = dep[v] + 1;
                q.push_back({to, v});
            }
        }
        return cnt;
    };
    // 距離の和が k になる (u, v) の順序付きの組の数
    auto ordered_pairs = [&](const vector<int>& cnt) {
        long long res = 0;
        for (int d = 0; d < (int)cnt.size(); d++) {
            int e = k - d;
            if (0 <= e && e < (int)cnt.size()) res += (long long)cnt[d] * cnt[e];
        }
        return res;
    };

    vector<int> stk = {0};  // これから分解する成分の代表の頂点
    while (!stk.empty()) {
        int r = stk.back();
        stk.pop_back();
        int c = find_centroid(r, g, removed, sz, par);
        // 重心 c を通る組 = 成分の全体の組 − 同じ子の成分の中の組
        long long through = ordered_pairs(depth_count(c, -1, 0));
        for (int to : g[c]) {
            if (removed[to]) continue;
            through -= ordered_pairs(depth_count(to, c, 1));
        }
        ans += through / 2;  // k ≥ 1 なので u = v の組はなく、順序付きの組は 2 回ずつ数えている
        removed[c] = 1;
        for (int to : g[c]) {
            if (!removed[to]) stk.push_back(to);
        }
    }
    return ans;
}
// --8<-- [end:core]

long long brute(int n, const vector<vector<int>>& g, int k) {
    long long res = 0;
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (dist[to] == -1) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        for (int t = s + 1; t < n; t++) {
            if (dist[t] == k) res++;
        }
    }
    return res;
}

int main() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 500; iter++) {
        int n = rng() % 14 + 1;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int p = (iter % 3 == 0) ? v - 1 : (int)(rng() % v);  // 3 回に 1 回はパス
            g[v].push_back(p);
            g[p].push_back(v);
        }
        for (int k = 1; k <= n; k++) assert(count_pairs_k(n, g, k) == brute(n, g, k));
    }

    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cout << count_pairs_k(n, g, k) << '\n';
}
