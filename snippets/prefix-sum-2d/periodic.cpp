#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<string> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    // t[i][j] = 1 枚のタイルの行 [0, i)・列 [0, j) にある黒（'B'）の数
    vector<vector<long long>> t(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i + 1][j + 1] = t[i][j + 1] + t[i + 1][j] - t[i][j] + (p[i][j] == 'B');
        }
    }
    // --8<-- [start:core]
    // f(x, y) = 敷き詰めた盤面の行 [0, x)・列 [0, y) にある黒の数（x, y ≥ 0）
    auto f = [&](long long x, long long y) {
        long long qx = x / n, rx = x % n, qy = y / n, ry = y % n;
        return qx * qy * t[n][n]      // 丸ごと入るタイル
             + qx * t[n][ry]          // 右端の余りの帯（qx 枚分）
             + qy * t[rx][n]          // 下端の余りの帯（qy 枚分）
             + t[rx][ry];             // 右下の角
    };
    // --8<-- [end:core]
    for (int k = 0; k < q; k++) {
        long long x1, y1, x2, y2;  // 行 [x1, x2)・列 [y1, y2)
        cin >> x1 >> y1 >> x2 >> y2;
        assert(0 <= x1 && x1 <= x2 && 0 <= y1 && y1 <= y2);
        cout << f(x2, y2) - f(x1, y2) - f(x2, y1) + f(x1, y1) << '\n';
    }
}
