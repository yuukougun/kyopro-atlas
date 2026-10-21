// 小さい素数 p を法とする C(n, k)（n, k は 10^18 まで）を Lucas の定理で求める。
// p 進法の各桁 n_i, k_i について C(n, k) ≡ Π C(n_i, k_i) (mod p)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, q;
    cin >> p >> q;
    // --8<-- [start:core]
    // 0 ≤ j ≤ i < p の C[i][j] mod p をパスカルの三角形で作る（O(p^2)）
    vector<vector<int>> C(p, vector<int>(p, 0));
    for (int i = 0; i < p; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % p;
    }
    auto lucas = [&](long long n, long long k) -> int {
        if (k < 0 || k > n) return 0;
        int res = 1;
        while (n > 0 || k > 0) {
            int ni = n % p, ki = k % p;   // p 進法の最下位の桁
            if (ki > ni) return 0;        // その桁で C(n_i, k_i) = 0
            res = res * C[ni][ki] % p;
            n /= p;
            k /= p;
        }
        return res;
    };
    // --8<-- [end:core]
    for (int t = 0; t < q; t++) {
        long long n, k;
        cin >> n >> k;
        cout << lucas(n, k) << '\n';
    }
}
