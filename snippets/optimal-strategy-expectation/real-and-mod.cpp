// 目 a_0, ..., a_{n-1} が等確率で出るサイコロを最大 K 回振れる。
// 振るたびに「やめてその目を得点にする」か「振り直す」かを選ぶ。
// 得点の期待値の最大値を mod 998244353 で出す（比べるのは実数、答えは mod）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// 残り k 回振れるときの期待値を、実数 er と mod の値 em の 2 通りで持つ
mint solve(const vector<long long>& a, int K) {
    int n = a.size();
    mint inv_n = mint(n).inv();
    double er = 0;  // 残り k - 1 回のときの値。k = 1 では振り直せないので使わない
    mint em = 0;
    for (int k = 1; k <= K; k++) {
        double nr = 0;
        mint nm = 0;
        for (int i = 0; i < n; i++) {
            // 振り直せる（k ≥ 2）うえ、振り直す方が実数で大きいときだけ振り直す
            if (k >= 2 && er > (double)a[i]) {
                nr += er;
                nm += em;  // mod は選んだ方を写すだけ
            } else {
                nr += (double)a[i];
                nm += a[i];
            }
        }
        er = nr / n;
        em = nm * inv_n;
    }
    return em;
}
// --8<-- [end:core]

int main() {
    int n, K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    assert(n >= 1 && K >= 1);
    cout << solve(a, K).val() << '\n';
}
