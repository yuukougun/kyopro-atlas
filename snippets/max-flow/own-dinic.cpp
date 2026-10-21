// Dinic 法を自分で書く例：BFS で s からの距離（層）を求め、層が 1 つずつ増える辺だけを
// たどる DFS で流せるだけ流す、をくり返す。各辺は逆辺の番号を持ち、流すと逆辺の容量が増える。
// 入力は N M s t と辺 (u, v, c)（0-indexed、有向）。結果を ACL の mf_graph と assert で比べる。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// --8<-- [start:core]
struct Dinic {
    struct Edge {
        int to, rev;    // 行き先と、行き先の隣接リストの中での逆辺の位置
        long long cap;  // 残りの容量
    };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    Dinic(int n) : g(n), level(n), iter(n) {}

    void add_edge(int from, int to, long long cap) {
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, (int)g[from].size() - 1, 0});  // 逆辺は容量 0 で始める
    }

    bool bfs(int s, int t) {  // 残余グラフでの s からの距離を level に入れる
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    long long dfs(int v, int t, long long up) {  // v まで up だけ届いているとき、t へ流せた量
        if (v == t) return up;
        for (int& i = iter[v]; i < (int)g[v].size(); i++) {  // 使い切った辺は二度と見ない
            Edge& e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            long long d = dfs(e.to, t, min(up, e.cap));
            if (d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;  // 逆辺に足す：後で押し戻せる
                return d;
            }
        }
        return 0;
    }

    long long flow(int s, int t) {
        long long total = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while (long long d = dfs(s, t, LLONG_MAX)) total += d;
        }
        return total;
    }
};
// --8<-- [end:core]

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic din(n);
    atcoder::mf_graph<long long> acl(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        din.add_edge(u, v, c);
        acl.add_edge(u, v, c);
    }
    long long f = din.flow(s, t);
    assert(f == acl.flow(s, t));
    cout << f << '\n';
    return 0;
}
