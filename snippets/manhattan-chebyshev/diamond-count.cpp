#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, q;
    cin >> h >> w >> q;
    vector<string> g(h);
    for (int r = 0; r < h; r++) cin >> g[r];
    // --8<-- [start:core]
    // マス (r, c) を (u, v) = (r + c, r − c + w − 1) に移す。u, v はどちらも [0, s) に入る
    int s = h + w - 1;
    vector<vector<int>> cnt(s + 1, vector<int>(s + 1, 0));  // 2 次元累積和（半開区間）
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            if (g[r][c] == '#') cnt[r + c + 1][r - c + w] += 1;
    for (int u = 1; u <= s; u++)
        for (int v = 1; v <= s; v++)
            cnt[u][v] += cnt[u - 1][v] + cnt[u][v - 1] - cnt[u - 1][v - 1];
    // |r − r0| + |c − c0| ≤ d のひし形 = 回転後の正方形 [u0 − d, u0 + d] × [v0 − d, v0 + d]
    auto count = [&](int r0, int c0, int d) -> int {
        int u0 = r0 + c0, v0 = r0 - c0 + w - 1;
        int ul = max(u0 - d, 0), ur = min(u0 + d + 1, s);  // [ul, ur) に切り詰める
        int vl = max(v0 - d, 0), vr = min(v0 + d + 1, s);
        return cnt[ur][vr] - cnt[ul][vr] - cnt[ur][vl] + cnt[ul][vl];
    };
    // --8<-- [end:core]
    for (int i = 0; i < q; i++) {
        int r0, c0, d;
        cin >> r0 >> c0 >> d;
        int ans = count(r0, c0, d);
        int brute = 0;
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                if (g[r][c] == '#' && abs(r - r0) + abs(c - c0) <= d) brute++;
        assert(ans == brute);
        cout << ans << '\n';
    }
}
