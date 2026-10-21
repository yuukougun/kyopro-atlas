#include <bits/stdc++.h>
using namespace std;

// 1 回に L 個以上 R 個以下を取る山の Grundy 数を、小さい山について表にする
vector<int> table(int L, int R, int n) {
    vector<int> g(n + 1, 0);
    for (int x = 0; x <= n; x++) {
        vector<bool> seen(R - L + 2, false);
        for (int t = L; t <= R && t <= x; t++) seen[g[x - t]] = true;
        int m = 0;
        while (seen[m]) m++;
        g[x] = m;
    }
    return g;
}

int main() {
    // --8<-- [start:core]
    // table(L, R, n) は、取れる個数を L, ..., R にした grundy_table と同じ
    // 実験：表を出力して規則を探す
    int L, R, n;
    cin >> L >> R >> n;
    vector<int> g = table(L, R, n);
    for (int x = 0; x <= n; x++) cout << g[x] << (x == n ? '\n' : ' ');

    // 確認：見つけた式 (x mod (L+R)) / L を、小さい L・R のすべてで表と比べる
    for (int l = 1; l <= 10; l++) {
        for (int r = l; r <= 20; r++) {
            vector<int> h = table(l, r, 500);
            for (int x = 0; x <= 500; x++) assert(h[x] == x % (l + r) / l);
        }
    }
    // --8<-- [end:core]
}
