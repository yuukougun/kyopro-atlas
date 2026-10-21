#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// N 個の位置の左端（位置 1）に黒玉を置き、1〜N から独立に一様に選んだ a, b の玉を
// 入れ替える操作を K 回行った後の、黒玉の位置の期待値。
// --8<-- [start:core]
mint expected_position(long long n, long long k) {
    mint inv_n2 = mint(n * n).inv();
    mint leave = mint(2 * (n - 1)) * inv_n2;  // 位置 1 から出ていく確率
    mint come = mint(2) * inv_n2;             // 特定の位置 j（j ≠ 1）から位置 1 へ来る確率
    mint p = 1;                               // p = 黒玉が位置 1 にいる確率
    for (long long i = 0; i < k; i++) {
        // 位置 1 以外にいる確率は合わせて 1 - p。どの位置 j にも (1 - p) / (n - 1) ずついる
        p = p * (1 - leave) + (1 - p) * come;
    }
    // 位置 2〜n は同じ確率なので、その部分の期待値は位置の平均 (n + 2) / 2 に 1 - p を掛けたもの
    return p + (1 - p) * mint(n + 2) / 2;
}
// --8<-- [end:core]

// 確かめ用：N 個の位置の確率をすべて持つ素朴な DP（O(K N^3)）
mint brute(int n, int k) {
    vector<mint> prob(n, 0);
    prob[0] = 1;
    mint inv_n2 = mint(n * n).inv();
    for (int t = 0; t < k; t++) {
        vector<mint> next(n, 0);
        for (int pos = 0; pos < n; pos++) {
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    int to = pos;
                    if (pos == a) to = b;
                    else if (pos == b) to = a;
                    next[to] += prob[pos] * inv_n2;
                }
            }
        }
        prob = next;
    }
    mint e = 0;
    for (int pos = 0; pos < n; pos++) e += prob[pos] * (pos + 1);
    return e;
}

// 閉じた式：p_K = 1/N + (1 - 1/N)(1 - 2/N)^K
mint closed_form(long long n, long long k) {
    mint inv_n = mint(n).inv();
    mint p = inv_n + (1 - inv_n) * (1 - 2 * inv_n).pow(k);
    return p + (1 - p) * mint(n + 2) / 2;
}

int main() {
    for (int n = 1; n <= 6; n++) {
        for (int k = 0; k <= 6; k++) {
            assert(expected_position(n, k) == brute(n, k));
            assert(expected_position(n, k) == closed_form(n, k));
        }
    }
    long long n, k;
    cin >> n >> k;
    cout << expected_position(n, k).val() << '\n';
}
