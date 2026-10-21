// '.' と '#'（穴）からなるグリッドで、穴を含まない正方形の個数と、最大の正方形の一辺を求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (int i = 0; i < h; i++) cin >> g[i];
    assert(h >= 1 && w >= 1);

    // --8<-- [start:core]
    // sq[i + 1][j + 1]：マス (i, j) を右下の角とする、穴を含まない最大の正方形の一辺
    // 0 行目と 0 列目は番兵（盤面の外は 0）なので、1 行目・1 列目の場合分けが要らない
    vector<vector<int>> sq(h + 1, vector<int>(w + 1, 0));
    long long count = 0;  // 個数は H×W×min(H, W) 程度まで増えるので long long
    int best = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (g[i][j] == '#') continue;  // 穴のマスを右下にする正方形はない（0 のまま）
            sq[i + 1][j + 1] = min({sq[i][j + 1], sq[i + 1][j], sq[i][j]}) + 1;  // 上・左・左上
            count += sq[i + 1][j + 1];  // 一辺 1, 2, …, sq の正方形がどれも条件を満たす
            best = max(best, sq[i + 1][j + 1]);
        }
    }
    cout << count << ' ' << best << '\n';
    // --8<-- [end:core]
}
