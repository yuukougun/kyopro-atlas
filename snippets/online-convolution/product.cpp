#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// (1 + a[0] x)(1 + a[1] x)...(1 + a[n-1] x) を展開する。O(n log^2 n)
vector<mint> product_of_linear(const vector<mint>& a) {
    // 添字の区間 [l, r) の一次式の積を、半分ずつに分けて掛ける
    auto prod = [&](auto&& self, int l, int r) -> vector<mint> {
        if (r - l == 1) return {mint(1), a[l]};
        int m = (l + r) / 2;
        return atcoder::convolution(self(self, l, m), self(self, m, r));
    };
    if (a.empty()) return {mint(1)};  // 空の積は 1
    return prod(prod, 0, (int)a.size());
}
// --8<-- [end:core]

// 左から 1 つずつ掛ける素朴な方法。O(n^2)
vector<mint> naive(const vector<mint>& a) {
    vector<mint> f = {mint(1)};
    for (mint x : a) {
        f.push_back(0);
        for (int k = (int)f.size() - 1; k >= 1; k--) f[k] += f[k - 1] * x;
    }
    return f;
}

int main() {
    mt19937 rng(1);
    for (int n = 0; n <= 300; n++) {
        vector<mint> a(n);
        for (auto& x : a) x = rng();
        assert(product_of_linear(a) == naive(a));
    }

    int n;
    cin >> n;
    vector<mint> a(n);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a[i] = x;
    }
    auto f = product_of_linear(a);
    for (int k = 0; k <= n; k++) cout << f[k].val() << (k == n ? '\n' : ' ');
}
