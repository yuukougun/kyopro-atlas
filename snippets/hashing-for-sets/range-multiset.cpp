// 多重集合のハッシュ：数列 a と b（値は 1 以上 n 以下）について、
// a[l, r) と b[L, R) が並べ替えで一致するかの質問に答える（0-indexed・半開区間）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) assert(1 <= a[i] && a[i] <= n && 1 <= b[i] && b[i] <= n);

    // --8<-- [start:core]
    // 値 v ごとに独立な 64 ビットの乱数 z[v]。シードは実行ごとに変える
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<unsigned long long> z(n + 1);
    for (int v = 1; v <= n; v++) z[v] = rng();

    // sa[i] = z[a[0]] + … + z[a[i-1]]（mod 2^64。unsigned のあふれは 2^64 を法とする計算になる）
    vector<unsigned long long> sa(n + 1, 0), sb(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sa[i + 1] = sa[i] + z[a[i]];
        sb[i + 1] = sb[i] + z[b[i]];
    }
    auto same = [&](int l, int r, int bl, int br) -> bool {
        if (r - l != br - bl) return false;           // 長さが違えば一致しない
        return sa[r] - sa[l] == sb[br] - sb[bl];      // 区間の多重集合のハッシュを比べる
    };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int l, r, bl, br;
        cin >> l >> r >> bl >> br;
        assert(0 <= l && l <= r && r <= n && 0 <= bl && bl <= br && br <= n);
        cout << (same(l, r, bl, br) ? "Yes" : "No") << '\n';
    }
}
