#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d.merge(a, b);
    }
    // --8<-- [start:core]
    auto gs = d.groups();  // 変数に受けてから回す（どの版でも安全）
    for (int v : gs[0]) cout << v << ' ';
    cout << '\n';
    for (const auto& g : d.groups()) cout << g.size() << ' ';  // 戻り値そのものを回すのも安全
    cout << '\n';
    // --8<-- [end:core]
}
