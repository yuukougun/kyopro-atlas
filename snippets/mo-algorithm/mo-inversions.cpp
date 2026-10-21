// Mo's algorithm と BIT：区間 [l, r) の転倒数を、多数のクエリで答える
// 左端と右端で増減が違うので、出し入れを 4 つの関数に分ける
// 入力：N Q、A_0 … A_{N-1}（0 ≤ A_i ≤ 10^9）、続く Q 行は「l r」（0-indexed の半開区間）
// 出力：各クエリの答え
// 起動時に、小さな乱数の入力で素朴な数え方と答えを比べる（assert）
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

template <class AddL, class AddR, class RemL, class RemR, class Answer>
void mo4(int n, const vector<pair<int, int>>& qs, AddL add_left, AddR add_right,
         RemL remove_left, RemR remove_right, Answer answer) {
    int q = qs.size();
    int B = max(1, (int)(n / sqrt(max(q, 1))));
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        int bi = qs[i].first / B, bj = qs[j].first / B;
        if (bi != bj) return bi < bj;
        return bi % 2 == 0 ? qs[i].second < qs[j].second : qs[i].second > qs[j].second;
    });
    int l = 0, r = 0;
    for (int k : ord) {
        auto [ql, qr] = qs[k];
        while (l > ql) add_left(--l);
        while (r < qr) add_right(r++);
        while (l < ql) remove_left(l++);
        while (r > qr) remove_right(--r);
        answer(k);
    }
}

vector<long long> solve(const vector<int>& a0, const vector<pair<int, int>>& qs) {
    int n = a0.size();
    // 値を 0 … m-1 に座標圧縮する
    vector<int> xs(a0.begin(), a0.end());
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int m = xs.size();
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = lower_bound(xs.begin(), xs.end(), a0[i]) - xs.begin();

    // --8<-- [start:core]
    atcoder::fenwick_tree<int> bit(m);  // 今の区間にある値ごとの個数
    int len = 0;                        // 今の区間の長さ
    long long cur = 0;                  // 今の区間の転倒数
    vector<long long> ans(qs.size());
    // 左端に入る要素は、区間の中の自分より小さい要素と組を作る
    auto add_left = [&](int i) { cur += bit.sum(0, a[i]); bit.add(a[i], 1); len++; };
    // 右端に入る要素は、区間の中の自分より大きい要素と組を作る
    auto add_right = [&](int i) { cur += len - bit.sum(0, a[i] + 1); bit.add(a[i], 1); len++; };
    // 出すときは、先に BIT から外してから同じ数を引く
    auto remove_left = [&](int i) { bit.add(a[i], -1); len--; cur -= bit.sum(0, a[i]); };
    auto remove_right = [&](int i) { bit.add(a[i], -1); len--; cur -= len - bit.sum(0, a[i] + 1); };
    mo4(n, qs, add_left, add_right, remove_left, remove_right, [&](int k) { ans[k] = cur; });
    // --8<-- [end:core]
    return ans;
}

long long brute(const vector<int>& a, int l, int r) {
    long long s = 0;
    for (int i = l; i < r; i++)
        for (int j = i + 1; j < r; j++)
            if (a[i] > a[j]) s++;
    return s;
}

int main() {
    mt19937 rng(2026);
    for (int t = 0; t < 200; t++) {
        int n = rng() % 30 + 1, q = rng() % 30 + 1;
        vector<int> a(n);
        for (auto& x : a) x = rng() % 6;
        vector<pair<int, int>> qs(q);
        for (auto& [l, r] : qs) {
            l = rng() % (n + 1);
            r = l + rng() % (n - l + 1);  // 空の区間も混ぜる
        }
        auto ans = solve(a, qs);
        for (int k = 0; k < q; k++) assert(ans[k] == brute(a, qs[k].first, qs[k].second));
    }

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<pair<int, int>> qs(q);
    for (auto& [l, r] : qs) cin >> l >> r;
    for (long long x : solve(a, qs)) cout << x << '\n';
}
