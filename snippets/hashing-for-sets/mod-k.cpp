// 各値が k の倍数個か：数列 a の空でない区間のうち、
// どの値も k の倍数回ずつ現れるものの個数を数える（k >= 2）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(k >= 2);
    for (int i = 0; i < n; i++) assert(1 <= a[i] && a[i] <= n);

    // --8<-- [start:core]
    // 組（値 v, 個数 c mod k）ごとに乱数を割り当てる。c = 0 の組は集合に入れない
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<vector<unsigned long long>> z(n + 1, vector<unsigned long long>(k, 0));
    for (int v = 1; v <= n; v++)
        for (int c = 1; c < k; c++) z[v][c] = rng();

    // h = 集合 {(v, 先頭 i 項での v の個数 mod k)} の XOR。区間 [l, i) の各値が
    // k の倍数個 ⇔ 先頭 l 項と先頭 i 項で各値の個数 mod k が等しい ⇔ ハッシュが等しい
    vector<int> cnt(n + 1, 0);
    unsigned long long h = 0;
    map<unsigned long long, long long> seen;  // これまでの接頭辞のハッシュの出現回数
    seen[h]++;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int v = a[i];
        h ^= z[v][cnt[v]];          // 古い組を除く（c = 0 なら z は 0 で何もしない）
        cnt[v] = (cnt[v] + 1) % k;
        h ^= z[v][cnt[v]];          // 新しい組を入れる
        ans += seen[h];             // 同じハッシュの接頭辞と組んだ区間を数える
        seen[h]++;
    }
    // --8<-- [end:core]
    cout << ans << '\n';
}
