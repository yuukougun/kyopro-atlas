// 2 次元いもす法：h 行 w 列の盤（初めはすべて 0）に、長方形 [x1, x2) × [y1, y2)（行 × 列）へ 1 を足す操作を
// n 回まとめて行い、最後に各マスの値を出力する。添字は 0-indexed。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, n;
    cin >> h >> w >> n;
    assert(h >= 1 && w >= 1 && n >= 0);

    // --8<-- [start:core]
    vector<vector<int>> d(h + 1, vector<int>(w + 1, 0));
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        assert(0 <= x1 && x1 <= x2 && x2 <= h && 0 <= y1 && y1 <= y2 && y2 <= w);
        d[x1][y1] += 1;  // 四隅に +1, −1, −1, +1
        d[x1][y2] -= 1;
        d[x2][y1] -= 1;
        d[x2][y2] += 1;
    }
    for (int x = 0; x <= h; x++)  // 横（列の向き）に累積
        for (int y = 1; y <= w; y++) d[x][y] += d[x][y - 1];
    for (int x = 1; x <= h; x++)  // 縦（行の向き）に累積
        for (int y = 0; y <= w; y++) d[x][y] += d[x - 1][y];
    // d[x][y]（0 <= x < h、0 <= y < w）が、マス (x, y) を覆う長方形の数
    // --8<-- [end:core]

    for (int x = 0; x < h; x++)
        for (int y = 0; y < w; y++) cout << d[x][y] << (y + 1 < w ? ' ' : '\n');
}
