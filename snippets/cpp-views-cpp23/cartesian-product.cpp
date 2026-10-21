#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    // --8<-- [start:core]
    // 上下左右に '#' がある '.' のマスを数える
    const int di[] = {1, -1, 0, 0}, dj[] = {0, 0, 1, -1};
    int cnt = 0;
    for (auto [i, j] : views::cartesian_product(views::iota(0, h), views::iota(0, w))) {
        if (g[i][j] != '.') continue;
        bool ok = false;
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (0 <= ni && ni < h && 0 <= nj && nj < w && g[ni][nj] == '#') ok = true;
        }
        cnt += ok;
    }
    // --8<-- [end:core]
    cout << cnt << '\n';
}
