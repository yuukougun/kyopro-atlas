// 部分ピボット選択をしない（0 でない最初の行をピボットにする）掃き出し法。
// 1e-20 x + y = 1, x + y = 2 で x が 0 になり、正しい値（ほぼ 1）から大きくずれることを確かめる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n + 1));
    for (auto& row : a) {
        for (auto& v : row) cin >> v;
    }
    for (int col = 0; col < n; col++) {
        int piv = col;
        while (a[piv][col] == 0) piv++;        // 0 でなければ、どんなに小さくても使う
        swap(a[piv], a[col]);
        for (int j = n; j >= col; j--) a[col][j] /= a[col][col];
        for (int i = 0; i < n; i++) {
            if (i == col) continue;
            double c = a[i][col];
            for (int j = col; j <= n; j++) a[i][j] -= c * a[col][j];
        }
    }
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) cout << a[i][n] << (i + 1 < n ? ' ' : '\n');
}
