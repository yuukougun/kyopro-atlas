#include <bits/stdc++.h>
using namespace std;

// 和が m 以下の非負整数列 B すべてにわたる Π C(B_i, A_i) の総和が
// C(m + N, S + N)（S = A の和）に等しいことを、小さい場合の全探索で確かめる。

long long C(long long n, long long r) {
    if (n < 0 || r < 0 || r > n) return 0;
    long long res = 1;
    for (long long i = 0; i < r; i++) res = res * (n - i) / (i + 1);
    return res;
}

// --8<-- [start:core]
// 1 列に並べた m + N 個の位置から S + N 個を選ぶ方法の数
long long closed_form(const vector<int>& a, int m) {
    int n = a.size();
    long long s = accumulate(a.begin(), a.end(), 0LL);
    return C(m + n, s + n);
}
// --8<-- [end:core]

long long brute(const vector<int>& a, int m) {
    int n = a.size();
    long long total = 0;
    auto dfs = [&](auto&& self, int i, int rest, long long prod) -> void {
        if (i == n) {
            total += prod;
            return;
        }
        for (int b = 0; b <= rest; b++) self(self, i + 1, rest - b, prod * C(b, a[i]));
    };
    dfs(dfs, 0, m, 1);
    return total;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    long long x = closed_form(a, m), y = brute(a, m);
    assert(x == y);
    cout << x << '\n';
}
