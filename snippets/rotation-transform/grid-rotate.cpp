// グリッドの回転・転置・反転の添字
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// h 行 w 列の盤面を時計回りに 90 度回す。結果は w 行 h 列で、(i, j) は (j, h - 1 - i) に移る
vector<string> rotate_cw(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    vector<string> r(w, string(h, '?'));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) r[j][h - 1 - i] = g[i][j];
    return r;
}

// 転置：(i, j) → (j, i)。左右の反転：(i, j) → (i, w - 1 - j)
vector<string> transpose(const vector<string>& g) {
    int h = g.size(), w = g[0].size();
    vector<string> r(w, string(h, '?'));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) r[j][i] = g[i][j];
    return r;
}

vector<string> flip_lr(const vector<string>& g) {
    vector<string> r = g;
    for (auto& row : r) reverse(row.begin(), row.end());
    return r;
}
// --8<-- [end:core]

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& s : g) cin >> s;

    // 4 回回すと元に戻る。時計回り 1 回 ＝ 転置してから左右の反転
    vector<string> r = g;
    for (int t = 0; t < 4; t++) r = rotate_cw(r);
    assert(r == g);
    assert(rotate_cw(g) == flip_lr(transpose(g)));

    for (const auto& row : rotate_cw(g)) cout << row << '\n';
}
