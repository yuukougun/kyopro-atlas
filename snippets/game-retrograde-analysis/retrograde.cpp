// 後退解析：有向グラフの頂点に駒があり、手番の人は辺に沿って 1 回動かす。動かせない方が負け。
// 各頂点（その頂点に駒があり、手番の人が動かす局面）が 勝ち W・負け L・引き分け D のどれかを求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> rev(n);  // 逆辺：rev[v] は v へ移れる局面の列
    vector<int> cnt(n, 0);       // 勝ちと確定していない行き先の数（最初は出次数）
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        rev[v].push_back(u);
        cnt[u]++;
    }

    // --8<-- [start:core]
    // res[v]：0 = 未確定（最後まで残れば引き分け）、1 = 勝ち、-1 = 負け（手番の人から見て）
    vector<int> res(n, 0);
    queue<int> q;
    for (int v = 0; v < n; v++) {
        if (cnt[v] == 0) {  // 動けない局面は負け
            res[v] = -1;
            q.push(v);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : rev[v]) {
            if (res[u] != 0) continue;  // 確定済みは変えない
            if (res[v] == -1) {
                res[u] = 1;  // 負けの局面へ移れるので勝ち
                q.push(u);
            } else if (--cnt[u] == 0) {
                res[u] = -1;  // 行き先がすべて勝ちなので負け
                q.push(u);
            }
        }
    }
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) {
        cout << (res[v] == 1 ? 'W' : res[v] == -1 ? 'L' : 'D');
    }
    cout << '\n';
}
