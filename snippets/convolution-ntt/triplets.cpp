#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

// 入力：N と、相異なる N 個の整数（0 以上）。
// 出力：B - A = C - B > 0 となる 3 つ組 (A, B, C)（どれも集合の要素）の数。

// --8<-- [start:core]
long long count_triplets(const vector<int>& s) {
    int v = *max_element(s.begin(), s.end());
    vector<long long> f(v + 1, 0);
    for (int x : s) f[x] = 1;  // 集合の指示関数
    // c[t] = 和が t になる順序付きの組 (x, y) の数（x = y も含む）。c[t] <= N なので mod で足りる
    vector<long long> c = atcoder::convolution(f, f);
    long long ans = 0;
    for (int b : s) {
        // A + C = 2B となる組から A = C = B の 1 組を除き、(A, C) と (C, A) の重複を 2 で割る
        ans += (c[2 * b] - 1) / 2;
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (auto& x : s) cin >> x;
    long long ans = count_triplets(s);
    // 全探索と一致することを確かめる
    set<int> st(s.begin(), s.end());
    long long brute = 0;
    for (int a : s) for (int b : s) if (b > a && st.count(2 * b - a)) brute++;
    assert(ans == brute);
    cout << ans << '\n';
}
