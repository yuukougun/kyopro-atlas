#include <bits/stdc++.h>
#include <atcoder/twosat>
using namespace std;

// --8<-- [start:core]
// リテラル lits[k] = (変数, 値) のうち、真になるのを高々 1 つにする。
// 補助変数 s_k（＝ lits[0..k] のどれかが真）に、変数 aux, aux+1, …, aux+K-1 を使う。
void at_most_one(atcoder::two_sat& ts, const vector<pair<int, bool>>& lits, int aux) {
    int k_max = lits.size();
    for (int k = 0; k < k_max; k++) {
        auto [v, b] = lits[k];
        int s = aux + k;
        ts.add_clause(v, !b, s, true);  // lits[k] → s_k
        if (k > 0) {
            ts.add_clause(s - 1, false, s, true);  // s_{k-1} → s_k
            ts.add_clause(s - 1, false, v, !b);    // s_{k-1} → ¬lits[k]
        }
    }
}
// --8<-- [end:core]

// K = 0..K_max の各 K と、真に固定するリテラルの集合 T のすべてで、
// 充足できる ⇔ |T| ≤ 1 を確かめる（リテラルの値の向きも 2 通り試す）
int main() {
    int k_max;
    cin >> k_max;
    int checked = 0;
    for (int k = 0; k <= k_max; k++) {
        for (int neg = 0; neg < 2; neg++) {
            for (int t = 0; t < (1 << k); t++) {
                atcoder::two_sat ts(2 * k);
                vector<pair<int, bool>> lits;
                for (int i = 0; i < k; i++) lits.push_back({i, neg == 0});
                at_most_one(ts, lits, k);
                for (int i = 0; i < k; i++) {
                    if (t >> i & 1) ts.add_clause(i, neg == 0, i, neg == 0);
                }
                bool ok = ts.satisfiable();
                assert(ok == (__builtin_popcount(t) <= 1));
                if (ok) {
                    vector<bool> x = ts.answer();
                    int cnt = 0;
                    for (int i = 0; i < k; i++) cnt += (x[i] == (neg == 0));
                    assert(cnt <= 1);
                }
                checked++;
            }
        }
    }
    cout << checked << '\n';
}
