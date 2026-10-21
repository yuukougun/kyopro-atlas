// 半開区間 [l, r) が n 本と、時刻 t のクエリが q 個ある。各クエリに、時刻 t を含む区間の数と、
// その中の重み w の最小値（なければ -1）を答える。開始・終了・クエリを (座標, 種類, 番号) にして並べ、
// 左から処理しながら、有効な区間の重みを multiset で持つ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> l(n), r(n), w(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i] >> w[i];
        assert(l[i] < r[i]);
    }
    vector<long long> t(q);
    for (int j = 0; j < q; j++) cin >> t[j];

    // --8<-- [start:core]
    // 種類の番号が同じ座標での処理順になる：終了 → 開始 → クエリ
    // （半開区間なので、r = t の区間はもう含まず、l = t の区間は含む）
    const int END = 0, START = 1, QUERY = 2;
    vector<tuple<long long, int, int>> ev;  // (座標, 種類, 区間かクエリの番号)
    for (int i = 0; i < n; i++) {
        ev.emplace_back(l[i], START, i);
        ev.emplace_back(r[i], END, i);
    }
    for (int j = 0; j < q; j++) ev.emplace_back(t[j], QUERY, j);
    sort(ev.begin(), ev.end());

    multiset<long long> active;  // 今の座標を含む区間の重み
    vector<long long> cnt(q), mn(q);
    for (auto [x, type, id] : ev) {
        if (type == START) {
            active.insert(w[id]);
        } else if (type == END) {
            active.erase(active.find(w[id]));  // erase(w[id]) だと同じ値がすべて消える
        } else {
            cnt[id] = active.size();
            mn[id] = active.empty() ? -1 : *active.begin();
        }
    }
    // --8<-- [end:core]
    for (int j = 0; j < q; j++) cout << cnt[j] << ' ' << mn[j] << '\n';  // 入力の順に出す
}
