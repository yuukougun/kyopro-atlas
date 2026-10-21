// 実数の連立一次方程式 Ax = b（A は n × n）を、部分ピボット選択つきの掃き出し法で解く。
// 入力：n、続く n 行に係数 n 個と右辺 1 個。出力：解を小数点以下 6 桁で（一意でなければ "singular"）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
constexpr double EPS = 1e-9;

// a は n 行 (n + 1) 列の拡大係数行列。解が一意なら x に入れて true を返す。
bool solve_real(vector<vector<double>> a, vector<double>& x) {
    int n = a.size();
    for (int col = 0; col < n; col++) {
        int piv = col;                         // 絶対値が最大の行をピボットにする
        for (int i = col + 1; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[piv][col])) piv = i;
        }
        if (fabs(a[piv][col]) < EPS) return false;   // 0 とみなす：一意でない
        swap(a[piv], a[col]);
        for (int j = n; j >= col; j--) a[col][j] /= a[col][col];
        for (int i = 0; i < n; i++) {
            if (i == col) continue;
            double c = a[i][col];
            for (int j = col; j <= n; j++) a[i][j] -= c * a[col][j];
        }
    }
    x.assign(n, 0);
    for (int i = 0; i < n; i++) x[i] = a[i][n];
    return true;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n + 1));
    for (auto& row : a) {
        for (auto& v : row) cin >> v;
    }
    vector<double> x;
    if (!solve_real(a, x)) {
        cout << "singular" << '\n';
        return 0;
    }
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) cout << x[i] << (i + 1 < n ? ' ' : '\n');
}
