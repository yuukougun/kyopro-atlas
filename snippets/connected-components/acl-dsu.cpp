#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    atcoder::dsu d(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d.merge(a - 1, b - 1);  // 1-indexed → 0-indexed
    }
    // groups() は O(N)。最後に 1 回だけ呼ぶ
    vector<vector<int>> gs = d.groups();
    int mx = 0;
    for (const auto& grp : gs) mx = max(mx, (int)grp.size());
    cout << gs.size() << ' ' << mx << '\n';  // 成分の数と最大の頂点数
    // --8<-- [end:core]
}
