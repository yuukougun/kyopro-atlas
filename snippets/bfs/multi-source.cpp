// 多始点 BFS：H×W のグリッド（'S' が始点、'#' が壁、'.' が床）で、各マスについて一番近い始点までの
// 歩数（上下左右）を求め、届くマスの歩数の最大と、どの始点からも届かない床の数を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) cin >> grid[i];

    // --8<-- [start:core]
    const int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> que;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'S') {  // 始点をすべて距離 0 で入れてから始める
                dist[i][j] = 0;
                que.push({i, j});
            }
        }
    }
    while (!que.empty()) {
        auto [i, j] = que.front();
        que.pop();
        for (int k = 0; k < 4; k++) {
            int ni = i + di[k], nj = j + dj[k];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;  // 範囲外
            if (grid[ni][nj] == '#' || dist[ni][nj] != -1) continue;  // 壁・発見済み
            dist[ni][nj] = dist[i][j] + 1;
            que.push({ni, nj});
        }
    }
    // --8<-- [end:core]

    int mx = -1, unreachable = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') continue;
            if (dist[i][j] == -1) unreachable++;  // -1 のまま max を取らない
            else mx = max(mx, dist[i][j]);
        }
    }
    cout << mx << ' ' << unreachable << '\n';
}
