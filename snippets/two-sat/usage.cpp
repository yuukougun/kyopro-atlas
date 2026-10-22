#include <bits/stdc++.h>
#include <atcoder/twosat>
using namespace std;

// 入力：n m、続けて m 行の「i f j g」（節 (x_i = f) ∨ (x_j = g)、f・g は 0 か 1）
// 出力：充足できれば Yes と割当（x_0 … x_{n-1} を 0・1 で）、できなければ No
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 4>> clauses(m);
    for (auto& [i, f, j, g] : clauses) cin >> i >> f >> j >> g;
    // --8<-- [start:core]
    atcoder::two_sat ts(n);
    for (auto [i, f, j, g] : clauses) {
        ts.add_clause(i, f, j, g);  // (x_i = f) ∨ (x_j = g)
    }
    if (!ts.satisfiable()) {
        cout << "No\n";
        return 0;
    }
    vector<bool> x = ts.answer();  // 最後の satisfiable() の割当
    // --8<-- [end:core]
    for (auto [i, f, j, g] : clauses) {
        assert(x[i] == bool(f) || x[j] == bool(g));
    }
    cout << "Yes\n";
    for (int v = 0; v < n; v++) cout << (x[v] ? 1 : 0);
    cout << '\n';
}
