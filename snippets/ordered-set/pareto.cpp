// 点 (a, b) の追加と、「a ≥ x の点の中での b の最大」の質問を処理する（追加だけで削除はない）。
// 入力：Q 行の「1 a b」（追加）・「2 x」（質問。該当する点がなければ -1）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    // --8<-- [start:core]
    // 支配されない点だけを持つ：a の昇順に並べると b は狭義の降順になる
    map<long long, long long> front;  // a → b
    auto add = [&](long long a, long long b) {
        auto it = front.lower_bound(a);  // a 以上で最小の点
        if (it != front.end() && it->second >= b) return;  // (a, b) は支配されるので入れない
        if (it != front.end() && it->first == a) it = front.erase(it);  // 同じ a で b が小さい点
        // 左側で b 以下の点は (a, b) に支配される。b は左ほど大きいので、すぐ左から続けて消える
        while (it != front.begin() && prev(it)->second <= b) front.erase(prev(it));
        front.emplace(a, b);
    };
    auto query = [&](long long x) -> long long {
        auto it = front.lower_bound(x);  // a ≥ x の点のうち a が最小のもの。b はこれが最大
        return it == front.end() ? -1 : it->second;
    };
    // --8<-- [end:core]
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            long long a, b;
            cin >> a >> b;
            add(a, b);
        } else {
            long long x;
            cin >> x;
            cout << query(x) << '\n';
        }
    }
    // 支配されない点だけが残り、b が狭義の降順に並んでいることを確かめる
    for (auto it = front.begin(); it != front.end() && next(it) != front.end(); ++it) {
        assert(it->second > next(it)->second);
    }
}
