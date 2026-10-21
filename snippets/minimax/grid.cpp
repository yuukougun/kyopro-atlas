// + と - のグリッドで、左上の駒を 2 人が交互に右か下へ 1 マス動かし、
// 動かした人が移動先のマスで +1 点か -1 点を得る。先手から見た勝敗（得点差の符号）を求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    assert(h >= 1 && w >= 1);

    // --8<-- [start:core]
    auto gain = [&](int i, int j) { return s[i][j] == '+' ? 1 : -1; };
    // f[i][j]：駒が (i, j) にあるとき、手番の人が以後に得る「自分 − 相手」の最大値
    vector<vector<int>> f(h, vector<int>(w, 0));  // 右下は終局なので 0
    for (int i = h - 1; i >= 0; i--) {
        for (int j = w - 1; j >= 0; j--) {
            if (i == h - 1 && j == w - 1) continue;
            int best = INT_MIN;  // 動ける手が少なくとも 1 つあるので必ず更新され、INT_MIN のまま反転されることはない
            if (i + 1 < h) best = max(best, gain(i + 1, j) - f[i + 1][j]);
            if (j + 1 < w) best = max(best, gain(i, j + 1) - f[i][j + 1]);
            f[i][j] = best;
        }
    }
    // 左上のマスは得点に入らない。f[0][0] は先手から見た差
    if (f[0][0] > 0) cout << "First\n";
    else if (f[0][0] < 0) cout << "Second\n";
    else cout << "Draw\n";
    // --8<-- [end:core]
}
