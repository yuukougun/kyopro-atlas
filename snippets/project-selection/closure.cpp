// 最大重み閉包：品物 i を選ぶと利益 p[i]（負もある）。「a を選ぶなら b も選ぶ」の条件を
// すべて満たす選び方のうち、利益の合計の最大値と、そのときに選ぶ品物を出力する。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    vector<pair<int, int>> req(m);
    for (auto& [a, b] : req) {
        cin >> a >> b;  // 0-indexed
        assert(0 <= a && a < n && 0 <= b && b < n);
    }

    // --8<-- [start:core]
    const long long INF = 1LL << 50;  // 正の利益の合計より大きい値
    int s = n, t = n + 1;              // s 側 = 選ぶ、t 側 = 選ばない
    atcoder::mf_graph<long long> g(n + 2);
    long long positive = 0;            // 正の利益の合計（全部取れたときの上限）
    for (int i = 0; i < n; i++) {
        if (p[i] > 0) {
            positive += p[i];
            g.add_edge(s, i, p[i]);    // 選ばないと p[i] を失う
        } else if (p[i] < 0) {
            g.add_edge(i, t, -p[i]);   // 選ぶと -p[i] を払う
        }
    }
    for (auto [a, b] : req) g.add_edge(a, b, INF);  // a を選び b を選ばない、を禁じる
    long long best = positive - g.flow(s, t);
    vector<bool> chosen = g.min_cut(s);  // s から届く頂点が「選ぶ」
    // --8<-- [end:core]

    long long check = 0;
    for (int i = 0; i < n; i++) if (chosen[i]) check += p[i];
    for (auto [a, b] : req) assert(!chosen[a] || chosen[b]);
    assert(check == best);
    cout << best << '\n';
    vector<int> ids;
    for (int i = 0; i < n; i++) if (chosen[i]) ids.push_back(i);
    for (int k = 0; k < (int)ids.size(); k++) cout << ids[k] << (k + 1 < (int)ids.size() ? " " : "");
    cout << '\n';
}
