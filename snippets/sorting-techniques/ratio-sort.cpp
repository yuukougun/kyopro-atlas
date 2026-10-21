// 比率の降順に並べる：人 i（1-indexed）の成功率 a_i / (a_i + b_i) が高い順に、
// 同じ率なら番号の小さい順に番号を出力する。比率は掛け算で比べ、stable_sort で同点の順を保つ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        assert(0 <= a[i] && a[i] <= 1000000000 && 0 <= b[i] && b[i] <= 1000000000);
        assert(a[i] + b[i] >= 1);  // 分母が 0 でない
    }

    // --8<-- [start:core]
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);  // 0, 1, …, n-1（番号の小さい順）
    // i の率が j の率より高いか：a_i / s_i > a_j / s_j を、分母を払って整数で比べる
    // （s は 2×10^9 以下なので、積は 2×10^18 以下で long long に収まる）
    stable_sort(idx.begin(), idx.end(), [&](int i, int j) {
        return a[i] * (a[j] + b[j]) > a[j] * (a[i] + b[i]);
    });
    // --8<-- [end:core]

    for (int k = 0; k < n; k++) cout << idx[k] + 1 << (k + 1 < n ? ' ' : '\n');
}
