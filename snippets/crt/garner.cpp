#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// --8<-- [start:core]
// 法 m[0..k) はどの 2 つも互いに素とする。x ≡ r[i] (mod m[i]) を満たす
// 0 <= x < m[0] * ... * m[k-1] の x を、x そのものを作らずに mod M で求める。
long long garner(vector<long long> r, vector<long long> m, long long M) {
    int k = r.size();
    m.push_back(M);
    // x = t[0] + t[1] m[0] + t[2] m[0] m[1] + ... と書いたときの、
    // 確定した項の和 mod m[j]（cons[j]）と、次の項の係数 m[0] ... m[i-1] mod m[j]（coef[j]）
    vector<long long> coef(k + 1, 1 % M), cons(k + 1, 0);
    for (int j = 0; j < k; j++) coef[j] = 1 % m[j];
    for (int i = 0; i < k; i++) {
        // cons[i] + t * coef[i] ≡ r[i] (mod m[i]) を t について解く
        long long d = ((r[i] - cons[i]) % m[i] + m[i]) % m[i];
        long long t = (long long)((__int128)d * atcoder::inv_mod(coef[i], m[i]) % m[i]);
        for (int j = i + 1; j <= k; j++) {
            cons[j] = (long long)((cons[j] + (__int128)t * coef[j]) % m[j]);
            coef[j] = (long long)((__int128)coef[j] * (m[i] % m[j]) % m[j]);
        }
    }
    return cons[k];
}
// --8<-- [end:core]

int main() {
    // 小さい法で、x を全部試した結果と一致することを確かめる
    vector<long long> ms = {3, 5, 7, 4};
    for (long long x = 0; x < 3 * 5 * 7 * 4; x++) {
        vector<long long> rs;
        for (long long mi : ms) rs.push_back(x % mi);
        assert(garner(rs, ms, 11) == x % 11);
        assert(garner(rs, ms, 1) == 0);
    }
    int k;
    long long M;
    cin >> k >> M;
    vector<long long> r(k), m(k);
    for (int i = 0; i < k; i++) cin >> r[i] >> m[i];
    cout << garner(r, m, M) << '\n';
}
