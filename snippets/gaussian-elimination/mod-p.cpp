// mod 998244353 の連立一次方程式 Ax = b を掃き出し法で解く。
// 入力：n m（式の数・変数の数）、続く n 行に係数 m 個と右辺 1 個。
// 出力：1 行目にランク、2 行目に none（解なし）か、解の個数の種類（unique / many）と解の 1 つ（自由変数は 0）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// a は n 行 (m + 1) 列の拡大係数行列（最後の列が右辺）。
// 係数の m 列を左から掃き出して簡約階段形にし、ランクを返す。
int sweep(vector<vector<mint>>& a, int m) {
    int n = a.size();
    int rank = 0;
    for (int col = 0; col < m && rank < n; col++) {
        int piv = -1;
        for (int i = rank; i < n; i++) {
            if (a[i][col].val() != 0) { piv = i; break; }
        }
        if (piv == -1) continue;               // この列の変数は自由変数になる
        swap(a[piv], a[rank]);
        mint inv = a[rank][col].inv();         // ピボットで割る＝逆元を掛ける
        for (int j = col; j <= m; j++) a[rank][j] *= inv;
        for (int i = 0; i < n; i++) {          // ほかのすべての行からこの列を消す
            if (i == rank || a[i][col].val() == 0) continue;
            mint c = a[i][col];
            for (int j = col; j <= m; j++) a[i][j] -= c * a[rank][j];
        }
        rank++;
    }
    return rank;
}

// 解がなければ空を返す。あれば自由変数を 0 にした解の 1 つを返す。
vector<mint> solve(vector<vector<mint>> a, int m, int& rank) {
    int n = a.size();
    rank = sweep(a, m);
    for (int i = rank; i < n; i++) {
        if (a[i][m].val() != 0) return {};     // 0 = (0 でない値) の行：解なし
    }
    vector<mint> x(m, 0);
    for (int i = 0; i < rank; i++) {
        int col = 0;
        while (a[i][col].val() == 0) col++;    // 行 i のピボットの列（値は 1）
        x[col] = a[i][m];
    }
    return x;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<mint>> a(n, vector<mint>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            long long v;
            cin >> v;
            a[i][j] = v;
        }
    }
    int rank;
    vector<mint> x = solve(a, m, rank);
    cout << rank << '\n';
    if (x.empty() && m > 0) {
        cout << "none" << '\n';
        return 0;
    }
    // 解を代入して確かめる
    for (int i = 0; i < n; i++) {
        mint s = 0;
        for (int j = 0; j < m; j++) s += a[i][j] * x[j];
        assert(s == a[i][m]);
    }
    cout << (rank == m ? "unique" : "many");
    for (int j = 0; j < m; j++) cout << ' ' << x[j].val();
    cout << '\n';
}
