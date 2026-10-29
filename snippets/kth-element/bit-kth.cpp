// 値ごとの個数の BIT で、多重集合の K 番目に小さい値を求める（BIT 上の二分探索）
// 入力：D Q、続く Q 行は「1 x」（値 x を 1 個追加。0 ≤ x < D）か「2 k」（k 番目に小さい値を出力して 1 個削除。なければ -1）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Fenwick {
    int n;
    vector<long long> t;  // t[i] は区間 (i - lowbit(i), i] の和（内部は 1-indexed）
    explicit Fenwick(int n) : n(n), t(n + 1, 0) {}
    void add(int p, long long x) {  // 外から見た 0-indexed の位置 p に x を足す
        for (int i = p + 1; i <= n; i += i & -i) t[i] += x;
    }
    long long sum(int r) {  // [0, r) の和
        long long s = 0;
        for (int i = r; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    // [0, r] の和が初めて k 以上になる 0-indexed の r を返す（k ≥ 1。全体の和が k 未満なら n）
    // 前提：すべての値が 0 以上
    int kth(long long k) {
        int pos = 0;  // 保つ性質：内部の (0, pos] の和 < 元の k、k は残りの個数
        for (int step = bit_floor((unsigned)n); step > 0; step >>= 1) {
            if (pos + step <= n && t[pos + step] < k) {  // t[pos + step] は (pos, pos + step] の和
                k -= t[pos + step];
                pos += step;
            }
        }
        return pos;  // 内部の位置 pos + 1 は、外から見た 0-indexed の pos
    }
};
// --8<-- [end:core]

int main() {
    int d, q;
    cin >> d >> q;
    Fenwick bit(d);
    multiset<int> naive;  // 素朴な方法で答えを確かめる
    for (int i = 0; i < q; i++) {
        int type;
        long long x;
        cin >> type >> x;
        if (type == 1) {
            bit.add(x, 1);
            naive.insert(x);
            continue;
        }
        int r = bit.kth(x);
        if (r == d) {  // k 個に満たない
            assert((long long)naive.size() < x);
            cout << -1 << '\n';
            continue;
        }
        assert(*next(naive.begin(), x - 1) == r);
        assert(bit.sum(r) < x && bit.sum(r + 1) >= x);
        cout << r << '\n';
        bit.add(r, -1);
        naive.erase(naive.find(r));
    }
}
