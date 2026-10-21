// 追加・削除のある集合で、x 以上の最小と x 未満の最大を答える。
// 入力：Q 行の「+ x」（追加）・「- x」（削除。ないときは何もしない）・「? x」（質問）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    // --8<-- [start:core]
    const long long INF = 2e18;  // 番兵。|x| ≤ 10^18 なら差を取ってもあふれない
    set<long long> st = {-INF, INF};
    // --8<-- [end:core]
    while (q--) {
        char op;
        long long x;
        cin >> op >> x;
        assert(-INF < x && x < INF);
        if (op == '+') {
            st.insert(x);
        } else if (op == '-') {
            st.erase(x);  // set なので値で消してよい（multiset なら find で 1 個だけ消す）
        } else {
            // --8<-- [start:query]
            auto it = st.lower_bound(x);  // 番兵 INF があるので end() にならない
            long long right = *it;        // x 以上で最小（なければ INF）
            long long left = *prev(it);   // x 未満で最大（番兵 -INF があるので begin() の前に出ない）
            // --8<-- [end:query]
            cout << (left == -INF ? string("-") : to_string(left)) << ' '
                 << (right == INF ? string("-") : to_string(right)) << '\n';
        }
    }
}
