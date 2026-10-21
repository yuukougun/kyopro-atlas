#include <bits/stdc++.h>
using namespace std;

// n の分割の数 p(n) を、漸化式の表と、降順の列だけを作る全列挙の 2 通りで求めて比べる
int main() {
    int n;
    cin >> n;

    // --8<-- [start:core]
    // p[i][k] = i を k 以下の正の整数の和で表す方法の数（順序は区別しない）
    vector<vector<long long>> p(n + 1, vector<long long>(n + 1, 0));
    for (int k = 0; k <= n; k++) p[0][k] = 1;  // 0 の分割は「何も使わない」1 通り
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            p[i][k] = p[i][k - 1];                      // k を 1 つも使わない
            if (i >= k) p[i][k] += p[i - k][k];         // k を 1 つ取り除く
        }
    }
    // p[n][n] が分割数 p(n)。p[i][0] は i >= 1 なら 0 のまま
    // --8<-- [end:core]

    // --8<-- [start:enumerate]
    vector<int> parts;   // 今の列（降順）
    long long leaves = 0;
    // rest = 残りの和、mx = 次に置いてよい最大の値（直前の値）
    auto dfs = [&](auto&& self, int rest, int mx) -> void {
        if (rest == 0) {
            leaves++;    // parts が 1 つの分割（ここで調べる）
            return;
        }
        for (int x = min(rest, mx); x >= 1; x--) {
            parts.push_back(x);
            self(self, rest - x, x);  // 次は x 以下だけ置ける
            parts.pop_back();
        }
    };
    dfs(dfs, n, n);
    // --8<-- [end:enumerate]

    assert(leaves == p[n][n]);
    cout << p[n][n] << '\n';
}
