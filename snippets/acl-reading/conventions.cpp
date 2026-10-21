#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    fenwick_tree<long long> fw(n);  // 添字は 0 から n - 1
    for (int i = 0; i < n; i++) fw.add(i, a[i]);
    cout << fw.sum(0, n) << '\n';   // 半開区間 [0, n) の和 = 全体の和
    cout << fw.sum(1, 1) << '\n';   // [1, 1) は空なので 0

    scc_graph g;       // 引数なしで作った物は、まだ使ってはいけない
    g = scc_graph(n);  // 代入してから使う
    // --8<-- [end:core]
    g.add_edge(0, n - 1);
    cout << g.scc().size() << '\n';
}
