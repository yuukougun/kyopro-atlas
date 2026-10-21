// 1 回 1 の費用でサイコロ（目 0, ..., n-1 が等確率）を振る。目 d が出たら、
// 仕上げの費用 c_d を払って終えるか、最初から振り直すかを選べる。
// 終えるまでの費用の期待値の最小値 X を、X を仮定して二分探索で求める。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 振り直したときの期待値を y と仮定して、始めの期待値 f(y) を計算する
double f(const vector<double>& c, double y) {
    double sum = 0;
    for (double cd : c) sum += min(cd, y);  // 終える・振り直すの安い方
    return 1 + sum / c.size();
}

double solve(const vector<double>& c) {
    double ok = 0;                                                       // X ≥ ok
    double ng = 1 + accumulate(c.begin(), c.end(), 0.0) / c.size() + 1;  // X < ng
    for (int it = 0; it < 100; it++) {
        double y = (ok + ng) / 2;
        if (f(c, y) > y) ok = y;  // 仮定が小さすぎる：本当の X は y より大きい
        else ng = y;
    }
    return ok;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<double> c(n);
    for (auto& x : c) cin >> x;
    assert(n >= 1);
    cout << fixed << setprecision(10) << solve(c) << '\n';
}
