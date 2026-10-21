#include <bits/stdc++.h>
using namespace std;

// N を 2 以上の数の積に順序付きで分ける方法の数（mod 998244353）を、
// N の約数を状態にした DP で求める。約数の組を全部見るので O(√N + d(N)^2)。
const long long MOD = 998244353;

// --8<-- [start:core]
// N の約数を昇順に列挙する：O(√N)
vector<long long> divisors(long long n) {
    vector<long long> small, large;
    for (long long i = 1; i <= n / i; i++) {
        if (n % i != 0) continue;
        small.push_back(i);
        if (i != n / i) large.push_back(n / i);
    }
    reverse(large.begin(), large.end());
    small.insert(small.end(), large.begin(), large.end());
    return small;
}

// dp[i] ＝ 約数 ds[i] を 2 以上の数の積に順序付きで分ける方法の数
long long count_factorizations(long long n) {
    vector<long long> ds = divisors(n);
    int k = ds.size();               // k = d(N)。10^12 以下なら 6720 以下
    vector<long long> dp(k, 0);
    dp[0] = 1;                       // ds[0] = 1：空の積
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < i; j++) {  // 約数の組を全部見る：O(k^2)
            if (ds[i] % ds[j] == 0) {  // 最後の因数が ds[i] / ds[j] (> 1)
                dp[i] = (dp[i] + dp[j]) % MOD;
            }
        }
    }
    return dp[k - 1];
}
// --8<-- [end:core]

int main() {
    assert(divisors(12) == vector<long long>({1, 2, 3, 4, 6, 12}));
    assert(divisors(36).size() == 9);  // 平方数で 6 を 2 回入れない
    long long n;
    cin >> n;
    cout << count_factorizations(n) << '\n';
}
