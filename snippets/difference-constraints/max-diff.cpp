// x_v - x_u <= c の形の条件の下で、x_t - x_s の最大値を求める。
// 入力：N M s t、続いて M 行の u v c（0-indexed。x_v - x_u <= c を表す）。
// 出力：条件を満たす解がなければ NO、x_t - x_s がいくらでも大きくできれば INF、それ以外は最大値。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long INF = LLONG_MAX / 4;  // INF + c でもあふれない大きさ

struct Constraint {
    int u, v;
    long long c;  // x_v - x_u <= c。辺 u -> v（重み c）として扱う
};

// 初期値 d から全辺の緩和を最大 n 回繰り返す。
// n 回とも更新が起きたら、d から届く負閉路があるので nullopt を返す
optional<vector<long long>> relax_all(int n, const vector<Constraint>& cs, vector<long long> d) {
    for (int iter = 0; iter < n; iter++) {
        bool updated = false;
        for (auto [u, v, c] : cs) {
            if (d[u] == INF) continue;  // まだ届いていない頂点からは緩和しない
            if (d[u] + c < d[v]) {
                d[v] = d[u] + c;
                updated = true;
            }
        }
        if (!updated) return d;
    }
    return nullopt;
}

// x_t - x_s の最大値。解がなければ nullopt、上限がなければ INF
optional<long long> max_diff(int n, const vector<Constraint>& cs, int s, int t) {
    // 1. 全頂点を 0 から始める（仮の始点から重み 0 の辺を全頂点へ張るのと同じ）。
    //    s から届かない負閉路もここで見つかる
    if (!relax_all(n, cs, vector<long long>(n, 0))) return nullopt;
    // 2. x_s = 0 として s からの最短距離を求める。dist[t] が x_t の最大値
    vector<long long> d(n, INF);
    d[s] = 0;
    auto dist = relax_all(n, cs, d);  // 1. で負閉路がないと分かっているので必ず値がある
    return (*dist)[t];
}
// --8<-- [end:core]

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<Constraint> cs(m);
    for (auto& [u, v, c] : cs) cin >> u >> v >> c;

    // 確かめ：解があるなら、0 から始めた最短距離はすべての条件を満たす
    if (auto x = relax_all(n, cs, vector<long long>(n, 0))) {
        for (auto [u, v, c] : cs) assert((*x)[v] - (*x)[u] <= c);
    }

    auto ans = max_diff(n, cs, s, t);
    if (!ans) {
        cout << "NO" << '\n';
    } else if (*ans == INF) {
        cout << "INF" << '\n';
    } else {
        cout << *ans << '\n';
    }
}
