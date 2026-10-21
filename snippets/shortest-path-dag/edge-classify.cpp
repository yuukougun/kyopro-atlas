// 無向グラフ（辺の重みは 1 以上）で、頂点 0 から頂点 n-1 への最短距離と最短路の本数（mod 998244353）を求め、
// 各辺を 0：どの最短路にも乗らない、1：ある最短路に乗る、2：すべての最短路に乗る、に分ける。
#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;
const long long MOD = 998244353;

struct Edge {
    int a, b;
    long long w;
};

vector<long long> dijkstra(int n, const vector<vector<pair<int, long long>>>& g, int src) {
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> es(m);
    vector<vector<pair<int, long long>>> g(n);
    for (auto& [a, b, w] : es) {
        cin >> a >> b >> w;
        a--, b--;
        assert(w >= 1);
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    int s = 0, t = n - 1;
    // --8<-- [start:on-path]
    vector<long long> ds = dijkstra(n, g, s), dt = dijkstra(n, g, t);

    long long D = ds[t];
    // 辺 a → b が s-t 最短路に乗る ⇔ ds[a] + w + dt[b] == D（両方の向きを調べる）
    auto on_path = [&](int a, int b, long long w) {
        return D < INF && ds[a] < INF && dt[b] < INF && ds[a] + w + dt[b] == D;
    };

    // s-t 最短路に乗る辺の区間 [ds[x], ds[y]) をいもす法で重ねる（座標は距離の値を圧縮）
    vector<long long> xs;
    vector<pair<long long, long long>> seg(m, {-1, -1});
    for (int i = 0; i < m; i++) {
        auto [a, b, w] = es[i];
        if (on_path(a, b, w)) seg[i] = {ds[a], ds[b]};
        else if (on_path(b, a, w)) seg[i] = {ds[b], ds[a]};
        if (seg[i].first >= 0) {
            xs.push_back(seg[i].first);
            xs.push_back(seg[i].second);
        }
    }
    // --8<-- [end:on-path]
    // --8<-- [start:classify]
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    auto idx = [&](long long x) { return int(lower_bound(xs.begin(), xs.end(), x) - xs.begin()); };
    int k = xs.size();
    vector<int> cover(k + 1, 0);
    for (int i = 0; i < m; i++) {
        if (seg[i].first < 0) continue;
        cover[idx(seg[i].first)]++;
        cover[idx(seg[i].second)]--;
    }
    for (int i = 0; i < k; i++) cover[i + 1] += cover[i];
    // extra[i] は、小区間 0..i-1 で重なりが 1 を超えた分の合計
    vector<long long> extra(k + 1, 0);
    for (int i = 0; i < k; i++) extra[i + 1] = extra[i] + max(0, cover[i] - 1);

    vector<int> kind(m, 0);
    for (int i = 0; i < m; i++) {
        if (seg[i].first < 0) continue;
        int l = idx(seg[i].first), r = idx(seg[i].second);
        kind[i] = (extra[r] - extra[l] == 0) ? 2 : 1;  // ほかの辺と重ならなければ、すべての最短路に乗る
    }
    // --8<-- [end:classify]

    // 最短路の本数：距離の小さい順は最短路 DAG のトポロジカル順（重みが正なので）
    vector<int> order;
    for (int v = 0; v < n; v++) {
        if (ds[v] < INF) order.push_back(v);
    }
    sort(order.begin(), order.end(), [&](int x, int y) { return ds[x] < ds[y]; });
    vector<long long> cnt(n, 0);
    cnt[s] = 1;
    for (int u : order) {
        for (auto [v, w] : g[u]) {
            if (ds[u] + w == ds[v]) cnt[v] = (cnt[v] + cnt[u]) % MOD;  // u → v は最短路 DAG の辺
        }
    }

    cout << (D < INF ? D : -1) << ' ' << cnt[t] << '\n';
    for (int i = 0; i < m; i++) cout << kind[i] << '\n';
}
