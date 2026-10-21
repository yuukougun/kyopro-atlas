// 仕事 i は処理時間 t_i・重み w_i（どちらも 0 以上）。1 台の機械で 1 つずつ処理し、
// 仕事 i の終了時刻を C_i として、重み付きの和 Σ w_i C_i の最小値を出力する。
// 隣接交換で導いた比較「t_i w_j < t_j w_i なら i が先」で並べる。小さい n では全順列と比べる。
#include <bits/stdc++.h>
using namespace std;

long long cost(const vector<long long>& t, const vector<long long>& w, const vector<int>& order) {
    long long time = 0, sum = 0;
    for (int i : order) {
        time += t[i];
        sum += w[i] * time;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    vector<long long> t(n), w(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> w[i];
        assert(0 <= t[i] && t[i] <= 1000000 && 0 <= w[i] && w[i] <= 1000000);
    }

    // --8<-- [start:core]
    // t = w = 0 の仕事は、どこに置いても和を変えない。比較では「どれとも同等」になり
    // 狭義の弱順序を壊すので、並べる対象から外す
    vector<int> order;
    for (int i = 0; i < n; i++) {
        if (t[i] != 0 || w[i] != 0) order.push_back(i);
    }
    // i を j より先に置くべきか：t_i / w_i < t_j / w_j を、割らずに掛け算で比べる
    sort(order.begin(), order.end(), [&](int i, int j) {
        return t[i] * w[j] < t[j] * w[i];
    });
    // --8<-- [end:core]

    long long ans = cost(t, w, order);
    if (n <= 8) {  // 全順列と比べて確かめる
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long best = LLONG_MAX;
        do {
            best = min(best, cost(t, w, p));
        } while (next_permutation(p.begin(), p.end()));
        assert(ans == best);
    }
    cout << ans << '\n';
}
