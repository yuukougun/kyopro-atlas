// mod 2 の連立一次方程式を bitset で掃き出し、解の個数を 998244353 で割った余りで出す。
// 入力：n m（式の数・変数の数）、続く n 行に長さ m の 0/1 の文字列（係数）と右辺 0/1。
// 出力：ランクと、解の個数 2^(m − rank)（解がなければ 0）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
constexpr int W = 2001;  // 変数の数 + 1（右辺の bit）以上にする

// 行 a[i] の bit j（j < m）が変数 j の係数、bit m が右辺。ランクを返す。
int sweep2(vector<bitset<W>>& a, int m) {
    int n = a.size();
    int rank = 0;
    for (int col = 0; col < m && rank < n; col++) {
        int piv = -1;
        for (int i = rank; i < n; i++) {
            if (a[i][col]) { piv = i; break; }
        }
        if (piv == -1) continue;
        swap(a[piv], a[rank]);                 // 1 で割る必要はない
        for (int i = 0; i < n; i++) {
            if (i != rank && a[i][col]) a[i] ^= a[rank];   // 行の引き算は XOR
        }
        rank++;
    }
    return rank;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<bitset<W>> a(n);
    for (int i = 0; i < n; i++) {
        string s;
        int b;
        cin >> s >> b;
        for (int j = 0; j < m; j++) a[i][j] = (s[j] == '1');
        a[i][m] = b;
    }
    // --8<-- [start:count]
    int rank = sweep2(a, m);
    bool ok = true;
    for (int i = rank; i < n; i++) {
        if (a[i][m]) ok = false;               // 係数がすべて 0 で右辺が 1：解なし
    }
    mint cnt = ok ? mint(2).pow(m - rank) : mint(0);
    // --8<-- [end:count]
    cout << rank << ' ' << cnt.val() << '\n';
}
