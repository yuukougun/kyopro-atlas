#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// i 回目の挑戦は確率 q[i] で成功し、成功するたびにコンボ L が 1 増えて L^2 点を得る。
// 最初に失敗した時点で終わる。得点の合計の期待値を返す。
// --8<-- [start:core]
mint expected_score(const vector<mint>& q) {
    // p = P(続いている)、s1 = E[L・1{続いている}]、s2 = E[L^2・1{続いている}]
    mint p = 1, s1 = 0, s2 = 0, ans = 0;
    for (mint qi : q) {
        // 成功した側だけが残り、L が L + 1 になる：(L + 1)^2 = L^2 + 2L + 1
        mint np = qi * p;
        mint ns1 = qi * (s1 + p);
        mint ns2 = qi * (s2 + 2 * s1 + p);
        p = np, s1 = ns1, s2 = ns2;
        ans += s2;  // この回に成功して得る L^2 の期待値
    }
    return ans;
}
// --8<-- [end:core]

// 確かめ用：成功・失敗の列をすべて列挙する
mint brute(const vector<mint>& q) {
    int n = q.size();
    mint ans = 0;
    for (int len = 0; len <= n; len++) {  // len 回続けて成功し、次で失敗（len = n なら最後まで成功）
        mint prob = 1;
        for (int i = 0; i < len; i++) prob *= q[i];
        if (len < n) prob *= 1 - q[len];
        long long score = 0;
        for (long long l = 1; l <= len; l++) score += l * l;
        ans += prob * score;
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<mint> q(n);
    for (int i = 0; i < n; i++) {
        int a;  // 成功する確率（%）
        cin >> a;
        q[i] = mint(a) / 100;
    }
    mint ans = expected_score(q);
    assert(ans == brute(q));
    cout << ans.val() << '\n';
}
