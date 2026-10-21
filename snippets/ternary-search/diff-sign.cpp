// 差分の符号で二分探索：x ∈ [0, 10^9] での f(x) = Σ w_i |x − a_i| の最小値を求める。
// f が下に凸なら f(x + 1) − f(x) は x について広義単調増加なので、「差分 ≥ 0」は単調な判定になる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), w(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> w[i];
    auto f = [&](long long x) {
        long long s = 0;
        for (int i = 0; i < n; i++) s += w[i] * llabs(x - a[i]);
        return s;
    };

    // --8<-- [start:core]
    const long long L = 0, R = 1'000'000'000;  // x の範囲は閉区間 [L, R]
    // check(x)：f(x + 1) − f(x) ≥ 0（x から右へ進んでも減らない）
    long long ng = L - 1;  // 番兵：L − 1 は判定しない
    long long ok = R;      // 番兵：右端は「これ以上右がない」ので可とみなす
    while (ok - ng > 1) {
        long long mid = ng + (ok - ng) / 2;
        if (f(mid + 1) - f(mid) >= 0) ok = mid;
        else ng = mid;
    }
    cout << f(ok) << '\n';  // ok は最小を与える x のうち最も左のもの
    // --8<-- [end:core]
}
