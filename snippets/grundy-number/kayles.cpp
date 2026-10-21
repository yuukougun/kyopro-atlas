#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int lim = max(n, 1000);  // 周期を探すために多めに計算する

    // --8<-- [start:core]
    // g[x] = x 本並んだピンの列の Grundy 数。1 回に 1 本か、隣り合う 2 本を倒す
    // t 本倒すと、残りは長さ a と x - t - a の 2 つの独立な列に分かれる
    vector<int> g(lim + 1, 0);
    for (int x = 1; x <= lim; x++) {
        vector<bool> seen(2 * x + 2, false);  // 行き先は 2x 個以下なので mex は 2x 以下
        for (int t = 1; t <= 2 && t <= x; t++) {
            for (int a = 0; a + t <= x; a++) {
                int v = g[a] ^ g[x - t - a];  // 2 つに分かれた局面は和なので XOR
                if (v < (int)seen.size()) seen[v] = true;
            }
        }
        int m = 0;
        while (seen[m]) m++;
        g[x] = m;
    }
    // --8<-- [end:core]

    for (int x = 0; x <= n; x++) cout << g[x] << (x == n ? '\n' : ' ');

    // --8<-- [start:period]
    // 計算した範囲の終わりまで g[x] = g[x + p] が続く最小の周期 p と、その始まり s を探す
    for (int p = 1; p <= 100; p++) {
        int s = lim - p;  // 後ろから、周期が崩れない限り始まりを前へ伸ばす
        while (s > 0 && g[s - 1] == g[s - 1 + p]) s--;
        if (s <= lim - 3 * p) {  // 3 周以上続かないものは周期とみなさない
            cout << "period " << p << " from " << s << '\n';
            break;
        }
    }
    // --8<-- [end:period]
}
