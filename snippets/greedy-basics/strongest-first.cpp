// 強い順に使う：くり返し使える a[i] と、1 回だけ使える b[i]（a[i] <= b[i]）があり、
// 合計 h 以上にするための最小の回数を求める。くり返し使う最大値 amax を基準にし、
// amax より強い 1 回限りのものだけを大きい順に使い、残りは amax でまとめて埋める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long h;
    cin >> n >> h;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    assert(n >= 1 && h >= 1);
    for (int i = 0; i < n; i++) assert(1 <= a[i] && a[i] <= b[i]);

    // --8<-- [start:core]
    long long amax = *max_element(a.begin(), a.end());  // くり返し使えるものの最強が基準
    sort(b.begin(), b.end(), greater<long long>());     // 1 回限りのものを強い順に
    long long count = 0;
    for (int i = 0; i < n && h > 0; i++) {
        if (b[i] <= amax) break;  // 基準以下なら、amax をくり返す方が悪くない
        h -= b[i];
        count++;
    }
    if (h > 0) count += (h + amax - 1) / amax;  // 残りは amax で埋める（切り上げ）
    cout << count << '\n';
    // --8<-- [end:core]
}
