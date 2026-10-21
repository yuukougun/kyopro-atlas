// 4 近傍の BFS：'.' が通れるマス、'#' が壁の H×W のグリッドで、
// 左上 (0, 0) から右下 (H-1, W-1) への最短の手数を求める（行けなければ -1）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    assert(h >= 1 && w >= 1);
    for (int i = 0; i < h; i++) assert(ssize(s[i]) == w);

    // --8<-- [start:core]
    // 上・右・下・左の順。(i, j) は i 行目・j 列目で、i が縦（行）、j が横（列）
    const int di[4] = {-1, 0, 1, 0};
    const int dj[4] = {0, 1, 0, -1};
    vector<vector<int>> dist(h, vector<int>(w, -1));  // -1 は未訪問の印を兼ねる
    queue<pair<int, int>> q;
    if (s[0][0] == '.') {
        dist[0][0] = 0;
        q.push({0, 0});
    }
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;  // 範囲外を先に弾く
            if (s[ni][nj] == '#' || dist[ni][nj] != -1) continue;
            dist[ni][nj] = dist[i][j] + 1;  // 印は push するときに付ける
            q.push({ni, nj});
        }
    }
    cout << dist[h - 1][w - 1] << '\n';
    // --8<-- [end:core]
}
