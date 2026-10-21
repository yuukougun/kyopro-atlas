#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<vector<long long>> a(h, vector<long long>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) cin >> a[i][j];
    }
    // --8<-- [start:core]
    // s[i][j] = 行 [0, i)・列 [0, j) の長方形の和。s[0][*] = s[*][0] = 0
    vector<vector<long long>> s(h + 1, vector<long long>(w + 1, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
        }
    }
    // 行 [x1, x2)・列 [y1, y2) の和（0-indexed、半開区間）
    auto rect = [&](int x1, int y1, int x2, int y2) {
        return s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
    };
    // --8<-- [end:core]
    assert(rect(0, 0, h, w) == s[h][w]);
    int q;
    cin >> q;
    for (int k = 0; k < q; k++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        assert(0 <= x1 && x1 <= x2 && x2 <= h && 0 <= y1 && y1 <= y2 && y2 <= w);
        cout << rect(x1, y1, x2, y2) << '\n';
    }
}
