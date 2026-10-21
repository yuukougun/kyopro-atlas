#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 時刻 s（整数）に出発すると s + c + floor(d / (s + 1)) に着く辺で、
// 時刻 t に始点にいて好きなだけ待てるときの、最も早い到着時刻
long long best_arrival(long long t, long long c, long long d) {
    // x = s + 1 とおく。x + floor(d / x) は x(x + 1) >= d となる最小の x で最小になり、
    // それより左では増えず、右では減らない
    long long x = sqrtl(d);
    while (x > 1 && (x - 1) * x >= d) x--;
    while (x * (x + 1) < d) x++;
    x = max(x, 1LL);
    long long s = max(t, x - 1);  // 最適な時刻まで待つ。もう過ぎていればすぐ出る
    return s + c + d / (s + 1);
}
// --8<-- [end:core]

int main() {
    // 小さい d と t で、待つ時刻を全部試した結果と比べる
    for (long long d = 0; d <= 3000; d++) {
        for (long long t = 0; t <= 80; t++) {
            long long best = LLONG_MAX;
            for (long long s = t; s <= max(t, d) + 1; s++) best = min(best, s + d / (s + 1));
            assert(best_arrival(t, 0, d) == best);
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long t, c, d;
        cin >> t >> c >> d;
        cout << best_arrival(t, c, d) << '\n';
    }
}
