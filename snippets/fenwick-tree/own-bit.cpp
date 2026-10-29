// 自作の BIT：内部は 1-indexed、外部は 0-indexed の半開区間。線形時間の構築と BIT 上の二分探索つき
// コンストラクタは ACL の fenwick_tree と同じ BIT()・BIT(n)（全要素 0）に、配列から線形時間で作る BIT(a) を足した
// 入力：N Q、a_0 … a_{N-1}（非負）、続く Q 行は「0 p x」（a_p += x、x ≥ 0）か「1 l r」（[l, r) の和）か
//       「2 w」（a_0 + … + a_r ≥ w となる最小の r。なければ N）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct BIT {
    int n;
    vector<long long> t;  // t[i]（1 ≤ i ≤ n）：区間 (i - lowbit(i), i] の和（1-indexed）
    BIT() : BIT(0) {}
    explicit BIT(int n) : n(n), t(n + 1, 0) {}  // 全要素 0（ACL の fenwick_tree(n) と同じ）
    explicit BIT(const vector<long long>& a) : n(a.size()), t(a.size() + 1, 0) {
        for (int i = 1; i <= n; i++) t[i] = a[i - 1];
        for (int i = 1; i <= n; i++) {  // 線形時間の構築：自分を親の箱へ足し込む
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
    void add(int p, long long x) {  // a_p += x（0 ≤ p < n）
        for (int i = p + 1; i <= n; i += i & -i) t[i] += x;  // i = 0 から始めると止まらない
    }
    long long sum(int r) const {  // a_0 + … + a_{r-1}（0 ≤ r ≤ n）
        long long s = 0;
        for (int i = r; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    long long sum(int l, int r) const { return sum(r) - sum(l); }  // [l, r) の和
    int lower_bound(long long w) const {  // a_0 + … + a_r ≥ w となる最小の r（値は非負、w ≥ 1）
        int pos = 0;                       // 不変条件：a の 1-indexed で [1, pos] の和 < w（減らした後の w に対して）
        int step = 1;
        while (step * 2 <= n) step *= 2;
        for (; step > 0; step /= 2) {
            if (pos + step <= n && t[pos + step] < w) {
                w -= t[pos + step];
                pos += step;
            }
        }
        return pos;  // 0-indexed の位置。総和 < w なら n
    }
};
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    BIT bit(a);  // 線形時間の構築
    BIT slow(n);  // 全要素 0 から add を n 回呼ぶ作り方（ACL と同じ。O(N log N)）
    for (int i = 0; i < n; i++) slow.add(i, a[i]);
    assert(bit.t == slow.t);  // 2 つの作り方で中の配列が一致する
    BIT empty;
    assert(empty.n == 0 && empty.sum(0) == 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long x;
            cin >> p >> x;
            bit.add(p, x);
            a[p] += x;
        } else if (t == 1) {
            int l, r;
            cin >> l >> r;
            long long res = bit.sum(l, r);
            assert(res == accumulate(a.begin() + l, a.begin() + r, 0LL));
            cout << res << '\n';
        } else {
            long long w;
            cin >> w;
            int res = bit.lower_bound(w);
            int check = 0;
            long long s = 0;
            while (check < n && s + a[check] < w) s += a[check++];
            assert(res == check);
            cout << res << '\n';
        }
    }
}
