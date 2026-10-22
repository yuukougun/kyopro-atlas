#include <bits/stdc++.h>
using namespace std;

// 実際は lib/fenwick_tree.hpp に置く。このコード片は 1 ファイルで動かすため、ヘッダの中身をここに書いた。
// --8<-- [start:header]
// #pragma once  ← 実際のヘッダでは 1 行目に書く（main のファイルに書くと警告が出るのでコメントにした）
#include <cassert>
#include <vector>

namespace mylib {

// 長さ n の列 a（初期値 0）に、1 点への加算と半開区間 [l, r) の和を O(log n) で答える。
// 制約：0 <= n、add は 0 <= p < n、sum は 0 <= l <= r <= n。
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
    int size() const { return n_; }

  private:
    int n_;
    std::vector<T> data_;
    T prefix(int r) const {  // [0, r) の和
        T s = 0;
        for (; r > 0; r -= r & -r) s += data_[r - 1];
        return s;
    }
};

}  // namespace mylib
// --8<-- [end:header]

int main() {
    // --8<-- [start:boundary]
    // 長さ 0：作れて、空区間の和は単位元の 0
    mylib::fenwick_tree<long long> empty(0);
    assert(empty.sum(0, 0) == 0);

    // 長さ 1：端の添字 0 と、区間 [0, 1)・[1, 1)
    mylib::fenwick_tree<long long> one(1);
    one.add(0, -5);
    assert(one.sum(0, 1) == -5 && one.sum(1, 1) == 0);

    // あふれ：int なら超える 3×10^9 を long long で持てるか
    mylib::fenwick_tree<long long> big(3);
    for (int i = 0; i < 3; i++) big.add(i, 1000000000);
    assert(big.sum(0, 3) == 3000000000LL);
    // --8<-- [end:boundary]

    // --8<-- [start:stress]
    // 愚直な配列と、乱数の操作で突き合わせる（種を固定して再現できるようにする）
    mt19937 rng(12345);
    for (int iter = 0; iter < 5000; iter++) {
        int n = rng() % 9;  // 0 も含む小さい長さ
        mylib::fenwick_tree<long long> fw(n);
        vector<long long> naive(n, 0);
        for (int q = 0; q < 20; q++) {
            if (n > 0 && rng() % 2 == 0) {
                int p = rng() % n;
                long long x = (long long)(rng() % 21) - 10;  // 負の値も入れる
                fw.add(p, x);
                naive[p] += x;
            } else {
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);  // l == r の空区間も出る
                long long expected = accumulate(naive.begin() + l, naive.begin() + r, 0LL);
                assert(fw.sum(l, r) == expected);
            }
        }
    }
    // --8<-- [end:stress]
    cout << "ok" << '\n';
}
