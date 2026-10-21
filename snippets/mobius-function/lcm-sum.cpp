#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

vector<int> mobius_table(int v) {
    vector<int> mu(v + 1, 1);
    vector<bool> is_prime(v + 1, true);
    for (int p = 2; p <= v; p++) {
        if (!is_prime[p]) continue;
        for (int j = p; j <= v; j += p) {
            if (j > p) is_prime[j] = false;
            mu[j] = -mu[j];
        }
        long long pp = (long long)p * p;
        for (long long j = pp; j <= v; j += pp) mu[j] = 0;
    }
    return mu;
}

// --8<-- [start:core]
// i < j についての lcm(a[i], a[j]) の総和（mod 998244353）。V は値の上限
mint lcm_pair_sum(const vector<int>& a) {
    int V = *max_element(a.begin(), a.end());
    vector<int> mu = mobius_table(V);
    // w(t) = Σ_{g | t} μ(t / g) / g とすると 1/gcd = Σ_{t | gcd} w(t)
    vector<mint> w(V + 1, 0);
    for (int g = 1; g <= V; g++) {
        mint inv_g = mint(g).inv();
        for (int t = g, d = 1; t <= V; t += g, d++) {
            if (mu[d] != 0) w[t] += mu[d] * inv_g;
        }
    }
    // s(t) = t の倍数である a[i] の和
    vector<mint> val(V + 1, 0);
    for (int x : a) val[x] += x;
    mint all = 0;  // 順序対 (i, j) すべての和（i = j を含む）
    for (int t = 1; t <= V; t++) {
        mint s = 0;
        for (int u = t; u <= V; u += t) s += val[u];
        all += w[t] * s * s;
    }
    mint diag = 0;  // i = j の分は lcm(a[i], a[i]) = a[i]
    for (int x : a) diag += x;
    return (all - diag) / 2;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    mint ans = lcm_pair_sum(a);
    if (n <= 2000) {
        mint brute = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) brute += (long long)a[i] / gcd(a[i], a[j]) * a[j];
        assert(ans == brute);
    }
    cout << ans.val() << '\n';
}
