#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

const int MAX = 200000;
vector<mint> fact(MAX + 1), ifact(MAX + 1);

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) fact[i] = fact[i - 1] * i;
    ifact[MAX] = fact[MAX].inv();
    for (int i = MAX; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

mint comb(int n, int r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fact[n] * ifact[r] * ifact[n - r];
}

// --8<-- [start:core]
// 種類ごとの個数が a[0], …, a[m-1] の並べ方 (Σa)! / (a[0]! … a[m-1]!)
mint multinomial(const vector<int>& a) {
    int n = 0;
    mint res = 1;
    for (int x : a) {
        n += x;
        res *= ifact[x];
    }
    return fact[n] * res;
}
// --8<-- [end:core]

// --8<-- [start:merge]

// 文字ごとの個数の上限 c[0], …, c[m-1] のもとで作れる、空でない文字列の個数。
// dp[len] ＝ ここまでの文字だけで作る長さ len の文字列の個数
mint count_strings(const vector<int>& c) {
    int total = 0;
    vector<mint> dp(1, 1);  // 空文字列が 1 個
    for (int x : c) {
        vector<mint> nd(total + x + 1);
        for (int len = 0; len <= total; len++) {
            if (dp[len] == 0) continue;
            for (int k = 0; k <= x; k++) {
                // 長さ len の列に新しい文字を k 個差し込む：位置の選び方は C(len + k, k)
                nd[len + k] += dp[len] * comb(len + k, k);
            }
        }
        dp = nd;
        total += x;
    }
    mint sum = 0;
    for (int len = 1; len <= total; len++) sum += dp[len];
    return sum;
}
// --8<-- [end:merge]

int main() {
    init();
    string s;
    cin >> s;
    vector<int> c(26, 0);
    for (char ch : s) c[ch - 'a']++;
    // 二項係数の積で順に場所を決めても同じ値になる
    mint by_binom = 1;
    int used = 0;
    for (int x : c) {
        used += x;
        by_binom *= comb(used, x);
    }
    assert(by_binom == multinomial(c));
    cout << multinomial(c).val() << ' ' << count_strings(c).val() << '\n';
}
