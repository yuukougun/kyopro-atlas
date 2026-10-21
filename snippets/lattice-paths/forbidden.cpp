// H×W のマスの左上から右下へ、右と下だけで進む経路のうち、左下の A×B のマス（下から A 行・左から B 列）に
// 入らないものの数を、法 10^9+7 で求める。列 B-1 から列 B へ移る行 h で分類して足す。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

vector<mint> fact, ifact;

void init_binom(int n_max) {
    fact.assign(n_max + 1, 1);
    ifact.assign(n_max + 1, 1);
    for (int i = 1; i <= n_max; i++) fact[i] = fact[i - 1] * i;
    ifact[n_max] = fact[n_max].inv();
    for (int i = n_max; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

mint binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    assert(n < (int)fact.size());
    return fact[n] * ifact[k] * ifact[n - k];
}

// 下に dr、右に dc 進む経路の数
mint paths(int dr, int dc) { return binom(dr + dc, dr); }

int main() {
    int h_size, w_size, a, b;
    cin >> h_size >> w_size >> a >> b;
    assert(1 <= a && a < h_size && 1 <= b && b < w_size);
    init_binom(h_size + w_size);  // 使う n は H + W - 2 以下

    // --8<-- [start:core]
    // マス (r, c) は 0-indexed。禁止は r ≥ H - A かつ c < B のマス。
    // どの経路も、列 B - 1 から列 B へちょうど 1 回だけ右に移る。その行 h（0 ≤ h < H - A）で分類する。
    mint ans = 0;
    for (int h = 0; h < h_size - a; h++) {
        mint left = paths(h, b - 1);                           // (0, 0) → (h, B - 1)
        mint right = paths(h_size - 1 - h, w_size - 1 - b);    // (h, B) → (H - 1, W - 1)
        ans += left * right;
    }
    cout << ans.val() << '\n';
    // --8<-- [end:core]
}
