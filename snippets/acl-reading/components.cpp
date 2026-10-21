#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    // --8<-- [start:core]
    dsu d(4);                        // Union-Find
    d.merge(0, 1);                   // d.same(0, 1)・d.leader(0)・d.size(0)
    fenwick_tree<long long> fw(4);   // BIT
    fw.add(2, 10);                   // fw.sum(l, r) は [l, r) の和
    scc_graph sg(3);                 // 強連結成分分解
    sg.add_edge(0, 1);               // sg.scc() は成分の列（トポロジカル順）
    two_sat ts(2);                   // 2-SAT。変数は 0, 1
    ts.add_clause(0, true, 1, false);  // 「x0 が真」または「x1 が偽」
    mf_graph<long long> mf(3);       // 最大流
    mf.add_edge(0, 1, 5);            // mf.flow(s, t) で s から t への最大流
    mcf_graph<long long, long long> mcf(3);  // 最小費用流
    mcf.add_edge(0, 1, 2, 3);        // 容量 2・費用 3。mcf.flow(s, t, 上限) は {流量, 費用}
    vector<long long> c = convolution(vector<long long>{1, 1}, vector<long long>{1, 2});  // 法 998244353 の畳み込み
    vector<int> sa = suffix_array(string("abab"));  // 接尾辞を辞書順に並べた開始位置
    vector<int> z = z_algorithm(string("abab"));    // z[i] は s と s[i, n) の最長共通接頭辞の長さ
    long long fs = floor_sum(4, 3, 1, 0);           // i = 0..3 の floor((1 * i + 0) / 3) の和
    auto [r, m] = crt({2, 3}, {3, 5});              // x ≡ 2 (mod 3)、x ≡ 3 (mod 5) の解 x ≡ r (mod m)
    // --8<-- [end:core]
    sg.add_edge(1, 0);
    mf.add_edge(1, 2, 3);
    mcf.add_edge(1, 2, 1, 1);
    cout << d.size(0) << ' ' << fw.sum(0, 3) << ' ' << sg.scc().size() << ' ' << ts.satisfiable() << '\n';
    cout << mf.flow(0, 2) << ' ' << mcf.flow(0, 2).second << '\n';
    for (long long v : c) cout << v << ' ';
    cout << '\n';
    for (int v : sa) cout << v << ' ';
    cout << '\n';
    for (int v : z) cout << v << ' ';
    cout << '\n' << fs << ' ' << r << ' ' << m << '\n';
}
