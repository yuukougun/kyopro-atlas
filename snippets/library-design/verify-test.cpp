// --8<-- [start:head]
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <bits/stdc++.h>
// #include "../lib/fenwick_tree.hpp"  ← 実際はこの 1 行（ここでは下に中身を書いた）
// --8<-- [end:head]
using namespace std;

// 実際は #include "../lib/fenwick_tree.hpp" の 1 行。このコード片は 1 ファイルで動かすため中身を書いた。
namespace mylib {
template <class T>
struct fenwick_tree {
    fenwick_tree() : n_(0) {}
    explicit fenwick_tree(int n) : n_(n), data_(n, T(0)) {}
    void add(int p, T x) {
        assert(0 <= p && p < n_);
        for (p++; p <= n_; p += p & -p) data_[p - 1] += x;
    }
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n_);
        return prefix(r) - prefix(l);
    }

  private:
    int n_;
    std::vector<T> data_;
    T prefix(int r) const {
        T s = 0;
        for (; r > 0; r -= r & -r) s += data_[r - 1];
        return s;
    }
};
}  // namespace mylib

// --8<-- [start:core]
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    mylib::fenwick_tree<long long> fw(n);
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        fw.add(i, a);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long x;
            cin >> p >> x;
            fw.add(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << fw.sum(l, r) << '\n';
        }
    }
}
// --8<-- [end:core]
