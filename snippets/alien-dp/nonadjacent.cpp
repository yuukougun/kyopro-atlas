// 隣り合わない要素をちょうど K 個選ぶ和の最大 f(K) を、2 つの方法で求める。
//   alien  ：罰金 λ を引いた制約なしの DP を、λ の二分探索で何度も解く（1 つの K の答え）
//   greedy ：取り消し付きの貪欲（優先度付きキューと連結リスト）で、すべての k の答えを出す
// どちらも、個数を状態に持つ素朴な DP と乱数の列で比べて確かめる。
// 入力：N K と列 A（|A_i| ≤ 10^6、1 ≤ K ≤ ceil(N/2)）。出力：alien の値と greedy の値。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:penalized]
// 1 個選ぶごとに lam を引いた和の最大と、そのときの個数（同点なら個数の少ない方）を返す
pair<long long, int> penalized(const vector<long long>& a, long long lam) {
    // ns：最後の要素を選ばない、s：最後の要素を選ぶ。値は (和, -個数) で比べる
    pair<long long, int> ns = {0, 0}, s = {LLONG_MIN / 4, 0};
    for (long long x : a) {
        pair<long long, int> take = {ns.first + x - lam, ns.second - 1};
        ns = max(ns, s);
        s = take;
    }
    pair<long long, int> best = max(ns, s);
    return {best.first, -best.second};
}
// --8<-- [end:penalized]

// --8<-- [start:alien]
long long alien(const vector<long long>& a, int k) {
    long long sum = 0;
    for (long long x : a) sum += llabs(x);
    // f(k) は [-sum, sum] に収まるので、傾き f(k+1) - f(k) は [-2sum, 2sum] に収まる
    long long lo = -2 * sum - 1, hi = 2 * sum + 1;  // cnt(lo) は最大の個数（k が最大のときだけ k と等しいが、結果は正しい）、cnt(hi) = 0 ≤ k
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (penalized(a, mid).second <= k) hi = mid;
        else lo = mid;
    }
    // hi は「個数の少ない方を選んでも k 以下」になる最小の λ。このとき k も最適な個数の 1 つ
    return penalized(a, hi).first + hi * k;
}
// --8<-- [end:alien]

// --8<-- [start:greedy]
// res[k] = 隣り合わない k 個を選ぶ和の最大（k = 0, 1, ..., ceil(N/2)）
vector<long long> greedy(const vector<long long>& a) {
    int n = a.size();
    const long long NEG = -(1LL << 50);  // 両端の番兵（選ばれない）
    vector<long long> val(n + 2, NEG);
    vector<int> L(n + 2), R(n + 2);
    vector<bool> removed(n + 2, false);
    priority_queue<pair<long long, int>> pq;
    for (int i = 0; i < n + 2; i++) {
        L[i] = max(i - 1, 0);
        R[i] = min(i + 1, n + 1);
    }
    for (int i = 1; i <= n; i++) {
        val[i] = a[i - 1];
        pq.push({val[i], i});
    }
    vector<long long> res = {0};
    while ((int)res.size() <= (n + 1) / 2) {
        auto [v, i] = pq.top();
        pq.pop();
        if (removed[i] || v != val[i]) continue;  // 消えた要素と古い値は読み飛ばす
        res.push_back(res.back() + v);
        int l = L[i], r = R[i];
        // i を選んだことを、「i をやめて両隣を選ぶ」差分の要素 1 つに置き換える
        val[i] = val[l] + val[r] - val[i];
        removed[l] = removed[r] = true;
        L[i] = L[l];
        R[i] = R[r];
        R[L[i]] = i;
        L[R[i]] = i;
        pq.push({val[i], i});
    }
    return res;
}
// --8<-- [end:greedy]

// 個数を状態に持つ素朴な DP：O(NK)
long long naive(const vector<long long>& a, int k) {
    const long long NEG = LLONG_MIN / 4;
    vector<long long> ns(k + 1, NEG), s(k + 1, NEG);
    ns[0] = 0;
    for (long long x : a) {
        vector<long long> nns(k + 1, NEG), ns2(k + 1, NEG);
        for (int j = 0; j <= k; j++) {
            nns[j] = max(ns[j], s[j]);
            if (j > 0 && ns[j - 1] > NEG) ns2[j] = ns[j - 1] + x;
        }
        ns = nns;
        s = ns2;
    }
    return max(ns[k], s[k]);
}

int main() {
    mt19937 rng(12345);
    for (int t = 0; t < 2000; t++) {
        int n = rng() % 9 + 1;
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng() % 21) - 8;  // 負の値と同じ値を混ぜる
        vector<long long> g = greedy(a);
        for (int k = 1; k <= (n + 1) / 2; k++) {
            long long want = naive(a, k);
            assert(alien(a, k) == want);
            assert(g[k] == want);
        }
    }
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << alien(a, k) << ' ' << greedy(a)[k] << '\n';
}
