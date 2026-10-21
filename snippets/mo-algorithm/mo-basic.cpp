// Mo's algorithm：区間の中で同じ値を持つ 3 つ組 (i < j < k) の個数を、多数のクエリで答える
// 入力：N Q、A_1 … A_N（1 ≤ A_i ≤ 200000）、続く Q 行は「L R」（1-indexed の閉区間）
// 出力：各クエリの答え
// 起動時に、小さな乱数の入力で素朴な数え方と答えを比べる（assert）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// クエリ [l, r) を並べ替え、add・remove で区間を 1 要素ずつ動かして答える
// add(i)・remove(i)：位置 i を区間に入れる・出す。answer(k)：今の区間で k 番目のクエリに答える
template <class Add, class Remove, class Answer>
void mo(int n, const vector<pair<int, int>>& qs, Add add, Remove remove, Answer answer) {
    int q = qs.size();
    int B = max(1, (int)(n / sqrt(max(q, 1))));  // ブロックの大きさ N/√Q
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        int bi = qs[i].first / B, bj = qs[j].first / B;
        if (bi != bj) return bi < bj;
        // 偶数番目のブロックは r の昇順、奇数番目は降順（r を往復させる）
        return bi % 2 == 0 ? qs[i].second < qs[j].second : qs[i].second > qs[j].second;
    });
    int l = 0, r = 0;  // 今の区間 [l, r)。最初は空
    for (int k : ord) {
        auto [ql, qr] = qs[k];
        while (l > ql) add(--l);  // 先に伸ばす
        while (r < qr) add(r++);
        while (l < ql) remove(l++);  // 後で縮める
        while (r > qr) remove(--r);
        answer(k);
    }
}
// --8<-- [end:core]

vector<long long> solve(const vector<int>& a, const vector<pair<int, int>>& qs) {
    int n = a.size();
    // --8<-- [start:triple]
    vector<long long> cnt(200001, 0);  // cnt[x]：今の区間にある値 x の個数
    long long cur = 0;                 // 今の区間の 3 つ組の個数
    vector<long long> ans(qs.size());
    auto add = [&](int i) {
        long long c = cnt[a[i]];
        cur += c * (c - 1) / 2;  // 新しい要素と、すでにある c 個から 2 つを選ぶ組
        cnt[a[i]]++;
    };
    auto remove = [&](int i) {
        cnt[a[i]]--;
        long long c = cnt[a[i]];
        cur -= c * (c - 1) / 2;  // 出す要素を含んでいた組
    };
    mo(n, qs, add, remove, [&](int k) { ans[k] = cur; });
    // --8<-- [end:triple]
    return ans;
}

long long brute(const vector<int>& a, int l, int r) {
    map<int, long long> c;
    for (int i = l; i < r; i++) c[a[i]]++;
    long long s = 0;
    for (auto [x, k] : c) s += k * (k - 1) * (k - 2) / 6;
    return s;
}

int main() {
    mt19937 rng(12345);
    for (int t = 0; t < 200; t++) {
        int n = rng() % 30 + 1, q = rng() % 30 + 1;
        vector<int> a(n);
        for (auto& x : a) x = rng() % 4 + 1;
        vector<pair<int, int>> qs(q);
        for (auto& [l, r] : qs) {
            l = rng() % n;
            r = l + 1 + rng() % (n - l);
        }
        auto ans = solve(a, qs);
        for (int k = 0; k < q; k++) assert(ans[k] == brute(a, qs[k].first, qs[k].second));
    }

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<pair<int, int>> qs(q);
    for (auto& [l, r] : qs) {
        cin >> l >> r;
        l--;  // 閉区間 [L, R]（1-indexed）を半開区間 [L-1, R)（0-indexed）に
    }
    for (long long x : solve(a, qs)) cout << x << '\n';
}
