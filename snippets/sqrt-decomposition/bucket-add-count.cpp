#include <bits/stdc++.h>
using namespace std;

// 区間加算 x と、区間内で y 以上の要素の個数を、ブロックの大きさ B の平方分割で処理する。
// 添字は 0-indexed、区間は半開区間 [l, r)。
// --8<-- [start:core]
struct BucketAddCount {
    int n, B, nb;
    vector<long long> a;               // 各要素の値（ブロックのタグは含まない）
    vector<long long> tag;             // tag[b]：ブロック b の全要素に足す値
    vector<vector<long long>> sorted;  // sorted[b]：ブロック b の a をソートしたもの
    BucketAddCount(const vector<long long>& a_, int B_)
        : n(a_.size()), B(B_), nb((n + B - 1) / B), a(a_), tag(nb, 0), sorted(nb) {
        for (int b = 0; b < nb; b++) rebuild(b);
    }
    void rebuild(int b) {              // ブロック b のソート済みの列を作り直す
        sorted[b].assign(a.begin() + b * B, a.begin() + min(n, (b + 1) * B));
        sort(sorted[b].begin(), sorted[b].end());
    }
    void add(int l, int r, long long x) {
        if (l >= r) return;
        int bl = l / B, br = (r - 1) / B;
        if (bl == br) {                // l と r - 1 が同じブロック
            for (int i = l; i < r; i++) a[i] += x;
            rebuild(bl);
            return;
        }
        for (int i = l; i < (bl + 1) * B; i++) a[i] += x;   // 左端のブロック
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) tag[b] += x;      // 丸ごと入るブロック
        for (int i = br * B; i < r; i++) a[i] += x;         // 右端のブロック
        rebuild(br);
    }
    int count_ge(int l, int r, long long y) {   // a_i + tag >= y となる i の個数
        if (l >= r) return 0;
        int bl = l / B, br = (r - 1) / B, res = 0;
        auto one = [&](int i) { if (a[i] + tag[i / B] >= y) res++; };
        if (bl == br) {
            for (int i = l; i < r; i++) one(i);
            return res;
        }
        for (int i = l; i < (bl + 1) * B; i++) one(i);
        for (int b = bl + 1; b < br; b++) {     // タグを y の側へ移して二分探索
            auto& s = sorted[b];
            res += s.end() - lower_bound(s.begin(), s.end(), y - tag[b]);
        }
        for (int i = br * B; i < r; i++) one(i);
        return res;
    }
};
// --8<-- [end:core]

void self_test() {
    mt19937 rng(20261021);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 20 + 1;
        int B = rng() % 5 + 1;
        vector<long long> a(n);
        for (auto& v : a) v = (long long)(rng() % 11) - 5;
        BucketAddCount bc(a, B);
        for (int q = 0; q < 50; q++) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            long long x = (long long)(rng() % 11) - 5;
            if (rng() % 2) {
                bc.add(l, r, x);
                for (int i = l; i < r; i++) a[i] += x;
            } else {
                int cnt = 0;
                for (int i = l; i < r; i++) cnt += a[i] >= x;
                assert(bc.count_ge(l, r, x) == cnt);
            }
        }
    }
}

int main() {
    self_test();
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    int B = max(1, (int)sqrt((double)n));
    BucketAddCount bc(a, B);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        long long x;
        cin >> t >> l >> r >> x;
        if (t == 1) bc.add(l, r, x);
        else cout << bc.count_ge(l, r, x) << '\n';
    }
}
