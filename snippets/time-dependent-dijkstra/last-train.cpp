#include <bits/stdc++.h>
using namespace std;

// 逆向きの辺。元の列車は to から出て、この辺を持つ頂点へ c かけて着く。
// 出発時刻は l, l + d, ..., l + (k - 1) d の k 本（時刻は 0 以上）
struct Train {
    int to;
    long long l, d, k, c;
};

const long long INF = LLONG_MAX;  // INF には足さず、c と l を引くだけなのでこの値でよい

// --8<-- [start:core]
// 時刻 t までに終点 u に着かなければならないとき、辺 e の始点を出られる最も遅い時刻（無理なら -1）
long long latest(long long t, const Train& e) {
    long long slack = t - e.c - e.l;  // 最初の列車から何分後の列車まで間に合うか
    if (slack < 0) return -1;         // 負の数の割り算を避けるため先に除く
    long long i = min(e.k - 1, slack / e.d);
    return e.l + i * e.d;
}

// late[v] = v を出て goal に間に合う最も遅い時刻（-1 は間に合わない）
vector<long long> latest_departure(const vector<vector<Train>>& rg, int goal) {
    int n = rg.size();
    vector<long long> late(n, -1);
    priority_queue<pair<long long, int>> pq;  // 最大ヒープ：遅い時刻から確定させる
    late[goal] = INF;
    pq.push({INF, goal});
    while (!pq.empty()) {
        auto [t, u] = pq.top();
        pq.pop();
        if (t != late[u]) continue;  // 古い組は読み飛ばす
        for (const Train& e : rg[u]) {
            long long s = latest(t, e);
            if (s > late[e.to]) {
                late[e.to] = s;
                pq.push({s, e.to});
            }
        }
    }
    return late;
}
// --8<-- [end:core]

// 確かめ用：変化がなくなるまで全辺で緩和を繰り返す
vector<long long> brute(const vector<vector<Train>>& rg, int goal) {
    int n = rg.size();
    vector<long long> late(n, -1);
    late[goal] = INF;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int u = 0; u < n; u++) {
            if (late[u] < 0) continue;
            for (const Train& e : rg[u]) {
                long long s = latest(late[u], e);
                if (s > late[e.to]) {
                    late[e.to] = s;
                    changed = true;
                }
            }
        }
    }
    return late;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Train>> rg(n);
    for (int i = 0; i < m; i++) {
        long long l, d, k, c;
        int a, b;
        cin >> l >> d >> k >> c >> a >> b;
        a--, b--;
        rg[b].push_back({a, l, d, k, c});  // 元は a → b
    }
    vector<long long> late = latest_departure(rg, n - 1);
    assert(late == brute(rg, n - 1));
    for (int v = 0; v < n - 1; v++) {
        if (late[v] < 0) {
            cout << "Unreachable" << '\n';
        } else {
            cout << late[v] << '\n';
        }
    }
}
