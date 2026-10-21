#include <bits/stdc++.h>
using namespace std;

// 1 次元の全ペアの |a_i − a_j| の和。ソートして、各要素を「左にある要素との差」として数える
long long pair_abs_sum(vector<long long> a) {
    sort(a.begin(), a.end());
    long long sum = 0, prefix = 0;  // prefix は a[0..i) の和
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i] * i - prefix;
        prefix += a[i];
    }
    return sum;
}

// --8<-- [start:core]
// 全ペアのチェビシェフ距離 max(|Δx|, |Δy|) の和。
// max(|a|, |b|) = (|a + b| + |a − b|) / 2 なので、u = x + y、v = x − y の
// マンハッタン距離の和を軸ごとに求めて 2 で割る（u と v の和の偶奇はそろうので割り切れる）
long long chebyshev_sum(const vector<long long>& x, const vector<long long>& y) {
    int n = x.size();
    vector<long long> u(n), v(n);
    for (int i = 0; i < n; i++) {
        u[i] = x[i] + y[i];
        v[i] = x[i] - y[i];
    }
    return (pair_abs_sum(u) + pair_abs_sum(v)) / 2;
}
// --8<-- [end:core]

long long brute(const vector<long long>& x, const vector<long long>& y) {
    long long s = 0;
    for (int i = 0; i < (int)x.size(); i++)
        for (int j = i + 1; j < (int)x.size(); j++)
            s += max(llabs(x[i] - x[j]), llabs(y[i] - y[j]));
    return s;
}

int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    long long ans = chebyshev_sum(x, y);
    if (n <= 2000) assert(ans == brute(x, y));
    cout << ans << '\n';
}
