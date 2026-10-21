// 線形篩：各合成数 x を「最小素因数 × 残り」の形でちょうど 1 回だけ作り、
// 最小素因数 lp と同時にオイラーの φ 関数・メビウス関数 μ の表を O(m) で作る。
// 入力：m と q 個の x。出力：m 以下の素数の個数と、各 x の「x φ(x) μ(x)」。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, q;
    cin >> m >> q;
    assert(1 <= m && m <= 10000000);

    // --8<-- [start:core]
    vector<int> lp(m + 1, 0), phi(m + 1, 0), mu(m + 1, 0), primes;
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= m; i++) {
        if (lp[i] == 0) {  // まだ作られていなければ素数
            lp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            primes.push_back(i);
        }
        // x = p * i を作る。p は lp[i] 以下の素数だけ（p が x の最小素因数になる）
        for (int p : primes) {
            if (p > lp[i] || (long long)p * i > m) break;
            int x = p * i;
            lp[x] = p;
            if (p == lp[i]) {  // p が i を割り切る：指数が 1 増える
                phi[x] = phi[i] * p;
                mu[x] = 0;
            } else {           // p は i の素因数でない：新しい素因数が 1 つ増える
                phi[x] = phi[i] * (p - 1);
                mu[x] = -mu[i];
            }
        }
    }
    // --8<-- [end:core]

    // 小さい範囲は素朴な素因数分解と照らし合わせる
    for (int x = 1; x <= min(m, 3000); x++) {
        int y = x, ph = x, mo = 1, small = 0;
        for (int d = 2; d * d <= y; d++) {
            if (y % d != 0) continue;
            if (small == 0) small = d;
            int e = 0;
            while (y % d == 0) y /= d, e++;
            ph = ph / d * (d - 1);
            mo = (e >= 2) ? 0 : -mo;
        }
        if (y > 1) {
            if (small == 0) small = y;
            ph = ph / y * (y - 1);
            mo = -mo;
        }
        assert(phi[x] == ph && mu[x] == mo);
        if (x >= 2) assert(lp[x] == small);
    }

    cout << primes.size() << '\n';
    for (int k = 0; k < q; k++) {
        int x;
        cin >> x;
        assert(1 <= x && x <= m);
        cout << x << ' ' << phi[x] << ' ' << mu[x] << '\n';
    }
}
