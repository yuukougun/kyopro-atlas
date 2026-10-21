#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// g[x] = 石が x 個の山の Grundy 数（1 回に moves のどれかの個数をちょうど取る）
vector<int> grundy_table(int maxa, const vector<int>& moves) {
    int k = moves.size();
    vector<int> g(maxa + 1, 0);
    for (int x = 0; x <= maxa; x++) {
        // 行き先は k 個以下なので、Grundy 数はどれも k 以下。印は k + 1 個で足りる
        vector<bool> seen(k + 1, false);
        for (int t : moves) {
            if (t <= x) seen[g[x - t]] = true;
        }
        int m = 0;
        while (seen[m]) m++;  // mex：印のない最小の値
        g[x] = m;
    }
    return g;
}
// --8<-- [end:core]

// --8<-- [start:move]
// 全体の XOR を 0 にする手を {山の番号, 取る個数} で返す。勝つ手がなければ {-1, -1}
pair<int, int> winning_move(const vector<int>& a, const vector<int>& g,
                            const vector<int>& moves) {
    int s = 0;
    for (int x : a) s ^= g[x];
    if (s == 0) return {-1, -1};
    for (int i = 0; i < (int)a.size(); i++) {
        int want = g[a[i]] ^ s;         // 山 i をこの Grundy 数の局面にすれば XOR が 0
        if (want >= g[a[i]]) continue;  // 小さくなる山だけが候補（mex の定義で必ず移れる）
        for (int t : moves) {
            if (t <= a[i] && g[a[i] - t] == want) return {i, t};
        }
    }
    return {-1, -1};  // s != 0 ならここには来ない
}
// --8<-- [end:move]

int main() {
    // 自己確認：1〜3 個取れるなら g(x) = x mod 4
    vector<int> g123 = grundy_table(20, {1, 2, 3});
    for (int x = 0; x <= 20; x++) assert(g123[x] == x % 4);

    int k;
    cin >> k;
    vector<int> moves(k);
    for (auto& t : moves) cin >> t;
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int maxa = 0;
    for (int x : a) maxa = max(maxa, x);

    vector<int> g = grundy_table(maxa, moves);
    auto [i, t] = winning_move(a, g, moves);
    if (i == -1) {
        cout << "Second" << '\n';
    } else {
        cout << "First " << i << ' ' << t << '\n';
    }
}
