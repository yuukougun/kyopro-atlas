// 答えの二分探索と完全マッチングの判定：N 人と N 個の目的地（どちらも整数の座標。座標が 10^9 程度までの場合）を 1 対 1 に組にし、
// 組の距離の最大値を最小にする。距離の 2 乗のまま比べ、最小の「距離の 2 乗の最大値」を出力する。
// 座標が 10^18 までなら距離の 2 乗は long long に収まらないので、d と候補を __int128 にする。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> px(n), py(n), qx(n), qy(n);
    for (int i = 0; i < n; i++) cin >> px[i] >> py[i];
    for (int j = 0; j < n; j++) cin >> qx[j] >> qy[j];
    vector<vector<long long>> d(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long dx = px[i] - qx[j], dy = py[i] - qy[j];
            d[i][j] = dx * dx + dy * dy;  // 整数のまま比べる（sqrt を取らない）
        }
    }

    // --8<-- [start:core]
    // check(x)：距離の 2 乗が x 以下の組だけを辺にして、完全マッチング（大きさ n）があるか
    auto check = [&](long long x) {
        int s = 2 * n, t = 2 * n + 1;
        atcoder::mf_graph<int> g(2 * n + 2);
        for (int i = 0; i < n; i++) {
            g.add_edge(s, i, 1);
            g.add_edge(n + i, t, 1);
            for (int j = 0; j < n; j++) {
                if (d[i][j] <= x) g.add_edge(i, n + j, 1);
            }
        }
        return g.flow(s, t) == n;
    };
    // 答えは d のどれかの値なので、候補を並べて添字で二分探索する
    vector<long long> cand;
    for (int i = 0; i < n; i++) cand.insert(cand.end(), d[i].begin(), d[i].end());
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    int ng = -1, ok = (int)cand.size() - 1;  // 最大の候補ならすべての辺があるので必ず可
    while (ok - ng > 1) {
        int mid = ng + (ok - ng) / 2;
        if (check(cand[mid])) ok = mid;
        else ng = mid;
    }
    cout << cand[ok] << '\n';
    // --8<-- [end:core]
}
