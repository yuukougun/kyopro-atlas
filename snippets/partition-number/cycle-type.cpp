#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 長さ n の順列すべてについて「元に戻るまでの回数（巡回の長さの lcm）」の k 乗を足す。
// n の分割（巡回型）を降順の列で全列挙し、巡回型ごとの順列の数を掛ける。
int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<mint> fact(n + 1, 1), inv(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        inv[i] = mint(i).inv();
    }

    // --8<-- [start:core]
    mint ans = 0;
    // rest = 残りの和、mx = 次に置いてよい最大の長さ、cnt = 直前の長さ mx を何個置いたか
    // l = ここまでの長さの lcm（整数のまま持つ）、w = 1 / Π(ℓ^m_ℓ · m_ℓ!) のここまでの分
    auto dfs = [&](auto&& self, int rest, int mx, int cnt, long long l, mint w) -> void {
        if (rest == 0) {
            ans += fact[n] * w * mint(l).pow(k);  // 巡回型ごとの数 × lcm^k
            return;
        }
        for (int x = min(rest, mx); x >= 1; x--) {
            int c = (x == mx ? cnt + 1 : 1);      // 長さ x の巡回がこれで c 個目
            // 長さ x の巡回 1 つで 1/x、同じ長さが c 個そろって 1/c!（ここで 1/c を掛ける）
            self(self, rest - x, x, c, lcm(l, (long long)x), w * inv[x] * inv[c]);
        }
    };
    dfs(dfs, n, n, 0, 1, 1);
    // --8<-- [end:core]

    // 小さい n では全部の順列を作って確かめる
    if (n <= 8) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        mint brute = 0;
        do {
            vector<bool> seen(n, false);
            long long l = 1;
            for (int i = 0; i < n; i++) {
                if (seen[i]) continue;
                int len = 0;
                for (int v = i; !seen[v]; v = p[v]) {
                    seen[v] = true;
                    len++;
                }
                l = lcm(l, (long long)len);
            }
            brute += mint(l).pow(k);
        } while (next_permutation(p.begin(), p.end()));
        assert(brute == ans);
    }
    cout << ans.val() << '\n';
}
