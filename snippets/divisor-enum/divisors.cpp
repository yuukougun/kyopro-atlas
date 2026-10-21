// 試し割り：i を √n まで動かし、素数判定と約数の列挙を O(√n) で行う。
// 入力 n（1 ≤ n ≤ 10^12）に対して、素数かどうかと、約数を小さい順に出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:prime]
// n が素数なら true。1 は素数ではない
bool is_prime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++) {  // i は long long（int だと i * i があふれる）
        if (n % i == 0) return false;          // √n 以下の約数が見つかれば合成数
    }
    return true;
}
// --8<-- [end:prime]

// --8<-- [start:divisors]
// n の約数を小さい順に返す
vector<long long> divisors(long long n) {
    vector<long long> res;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i != 0) continue;
        res.push_back(i);                    // 小さい方 i ≤ √n
        if (i != n / i) res.push_back(n / i);  // 大きい方 n / i ≥ √n（平方数で i = n / i なら 1 回だけ）
    }
    sort(res.begin(), res.end());  // i と n / i が交互に入るので並べ直す
    return res;
}
// --8<-- [end:divisors]

int main() {
    long long n;
    cin >> n;
    assert(1 <= n && n <= 1000000000000LL);
    cout << (is_prime(n) ? "prime" : "not prime") << '\n';
    vector<long long> d = divisors(n);
    for (int i = 0; i < (int)d.size(); i++) cout << d[i] << (i + 1 == (int)d.size() ? '\n' : ' ');
}
