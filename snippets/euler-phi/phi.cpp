#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:single]
// φ(n) を試し割りで求める。O(√n)
long long euler_phi(long long n) {
    long long res = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p != 0) continue;
        res -= res / p;              // res に (1 - 1/p) を掛ける（割り切れる）
        while (n % p == 0) n /= p;   // 素因数 p を取り除く
    }
    if (n > 1) res -= res / n;       // 残った n は √n より大きい素因数
    return res;
}
// --8<-- [end:single]

// --8<-- [start:sieve]
// φ(0), φ(1), ..., φ(N) を篩で求める。O(N log log N)
vector<int> phi_table(int N) {
    vector<int> phi(N + 1);
    for (int i = 0; i <= N; i++) phi[i] = i;
    for (int p = 2; p <= N; p++) {
        if (phi[p] != p) continue;   // 書き換えられていなければ p は素数
        for (int m = p; m <= N; m += p) phi[m] -= phi[m] / p;
    }
    return phi;
}
// --8<-- [end:sieve]

int main() {
    // 素朴な数え方・篩・約数についての和で、互いに確かめる
    const int V = 3000;
    vector<int> phi = phi_table(V);
    for (int n = 1; n <= V; n++) {
        int cnt = 0;
        for (int k = 1; k <= n; k++) if (gcd(k, n) == 1) cnt++;
        assert(cnt == phi[n]);
        assert(euler_phi(n) == phi[n]);
        int sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += phi[d];
        assert(sum == n);  // Σ_{d|n} φ(d) = n
    }
    long long n;
    cin >> n;
    cout << euler_phi(n) << '\n';
}
