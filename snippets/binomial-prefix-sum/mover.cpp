// 二項係数の部分和 S(n, K) = Σ_{0≤k≤K} C(n, k) を mod 998244353 で、
// 状態 (n, K) を 1 ずつ動かしながら O(1) で更新する。
// 入力：n_max Q と Q 個のクエリ (n, K)（0 ≤ n ≤ n_max、-1 ≤ K ≤ n_max）。
// クエリを Mo's algorithm の順に並べて処理し、入力の順に答える。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

vector<mint> fact, ifact;

void init_binom(int n_max) {
    fact.assign(n_max + 1, 1);
    ifact.assign(n_max + 1, 1);
    for (int i = 1; i <= n_max; i++) fact[i] = fact[i - 1] * i;
    ifact[n_max] = fact[n_max].inv();
    for (int i = n_max; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

mint binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;  // 範囲外は 0
    return fact[n] * ifact[k] * ifact[n - k];
}

// --8<-- [start:core]
// 保つ性質：s == S(n, k) = C(n, 0) + C(n, 1) + ... + C(n, k)（k < 0 なら 0）
struct BinomPrefix {
    int n = 0, k = 0;
    mint s = 1;  // S(0, 0) = 1
    const mint inv2 = mint(2).inv();

    void inc_k() { k++; s += binom(n, k); }                // S(n, k+1) = S(n, k) + C(n, k+1)
    void dec_k() { s -= binom(n, k); k--; }                // S(n, k-1) = S(n, k) - C(n, k)
    void inc_n() { s = s * 2 - binom(n, k); n++; }         // S(n+1, k) = 2 S(n, k) - C(n, k)
    void dec_n() { n--; s = (s + binom(n, k)) * inv2; }    // S(n-1, k) = (S(n, k) + C(n-1, k)) / 2
};
// --8<-- [end:core]

int main() {
    int n_max, q;
    cin >> n_max >> q;
    init_binom(n_max);
    vector<int> qn(q), qk(q);
    for (int i = 0; i < q; i++) cin >> qn[i] >> qk[i];

    // Mo's algorithm の順：n をブロックに分け、ブロックの中は k の順（奇数ブロックは逆順）
    int block = max(1, (int)(n_max / sqrt(max(q, 1))));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        int ba = qn[a] / block, bb = qn[b] / block;
        if (ba != bb) return ba < bb;
        return (ba % 2 == 0) ? qk[a] < qk[b] : qk[a] > qk[b];
    });

    BinomPrefix st;
    vector<mint> ans(q);
    for (int i : order) {
        // (n, K) には通ってはいけない状態がないので、4 つの while の順は自由（区間の Mo にそろえた）
        while (st.k < qk[i]) st.inc_k();
        while (st.n < qn[i]) st.inc_n();
        while (st.k > qk[i]) st.dec_k();
        while (st.n > qn[i]) st.dec_n();
        ans[i] = st.s;
    }
    if (n_max <= 60) {  // 小さい n では愚直な和と比べて確かめる
        for (int i = 0; i < q; i++) {
            mint brute = 0;
            for (int j = 0; j <= qk[i]; j++) brute += binom(qn[i], j);
            assert(ans[i] == brute);
        }
    }
    for (int i = 0; i < q; i++) cout << ans[i].val() << '\n';
}
