// 試し割りによる素因数分解：n = p1^e1 × p2^e2 × … の (p, e) を p の小さい順に返す。
// 入力 n（1 ≤ n ≤ 10^18）。出力は素因数の種類数 k と、k 行の「p e」。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> res;
    for (long long i = 2; i * i <= n; i++) {  // n は割るたびに小さくなる
        if (n % i != 0) continue;
        int e = 0;
        while (n % i == 0) {  // 割れるだけ割る
            n /= i;
            e++;
        }
        res.push_back({i, e});  // ここで見つかる i は必ず素数
    }
    if (n > 1) res.push_back({n, 1});  // 残りは √(元の n) を超える素数 1 個
    return res;
}
// --8<-- [end:core]

int main() {
    long long n;
    cin >> n;
    assert(1 <= n);
    auto f = factorize(n);
    cout << f.size() << '\n';
    for (auto [p, e] : f) cout << p << ' ' << e << '\n';
}
