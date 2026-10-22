// 向きを状態に持つ 01-BFS：迷路で、スタートからゴールまでに向きを変える回数の最小値を求める。
// 入力：H W、sr sc gr gc（0-indexed）、続く H 行に '.'（通れる）と '#'（壁）。行けなければ -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, sr, sc, gr, gc;
    cin >> h >> w >> sr >> sc >> gr >> gc;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) cin >> grid[i];
    assert(grid[sr][sc] == '.' && grid[gr][gc] == '.');

    // --8<-- [start:core]
    const int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};  // 上・右・下・左
    const int INF = INT_MAX;
    // 状態 (i, j, d) を (i * w + j) * 4 + d に詰める。頂点数はマスの数の 4 倍
    auto id = [&](int i, int j, int d) { return (i * w + j) * 4 + d; };
    vector<int> dist(h * w * 4, INF);
    deque<pair<int, int>> dq;  // (距離, 状態)
    for (int d = 0; d < 4; d++) {  // 最初の向きは自由に選べるので、4 つとも距離 0
        dist[id(sr, sc, d)] = 0;
        dq.push_back({0, id(sr, sc, d)});
    }
    while (!dq.empty()) {
        auto [cost, st] = dq.front();
        dq.pop_front();
        if (cost > dist[st]) continue;
        int d = st % 4, i = st / 4 / w, j = st / 4 % w;
        // 同じ向きに 1 マス進む：重み 0
        int ni = i + di[d], nj = j + dj[d];
        if (0 <= ni && ni < h && 0 <= nj && nj < w && grid[ni][nj] == '.' && cost < dist[id(ni, nj, d)]) {
            dist[id(ni, nj, d)] = cost;
            dq.push_front({cost, id(ni, nj, d)});
        }
        // その場で向きを変える：重み 1
        for (int e = 0; e < 4; e++) {  // e：向きを変えた先
            if (e == d || cost + 1 >= dist[id(i, j, e)]) continue;
            dist[id(i, j, e)] = cost + 1;
            dq.push_back({cost + 1, id(i, j, e)});
        }
    }
    int ans = INF;
    for (int d = 0; d < 4; d++) ans = min(ans, dist[id(gr, gc, d)]);  // 着いたときの向きは問わない
    // --8<-- [end:core]

    cout << (ans == INF ? -1 : ans) << '\n';
}
