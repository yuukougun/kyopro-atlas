// 距離表からの復元：N 頂点の距離表 A（対角は 0、ほかは正、対称）が与えられ、
// A をちょうど最短距離に持つ無向グラフがあるかを判定し、あれば辺の長さの和の最小値を出力する（なければ -1）。
// 入力は N と N 行 N 列の A。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long restore(const vector<vector<long long>>& a) {
    int n = a.size();
    // 1. 三角不等式：どこかを経由して短くなる組があれば、A は最短距離になれない
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][k] + a[k][j] < a[i][j]) return -1;
    // 2. 迂回できない組 (i, j) にだけ長さ A[i][j] の辺を張る
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool detour = false;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;  // k = i, j を除かないと、どの組も迂回できることになる
                if (a[i][k] + a[k][j] == a[i][j]) detour = true;  // 同じ長さの迂回路があれば要らない
            }
            if (!detour) sum += a[i][j];
        }
    }
    return sum;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    cout << restore(a) << '\n';
}
