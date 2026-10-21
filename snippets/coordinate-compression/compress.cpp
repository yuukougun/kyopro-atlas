// 座標圧縮：値の列 a を、大小関係を保ったまま 0〜K−1 の番号の列 id に置き換える。
// 同じ値には同じ番号を付け、vals[id[i]] == a[i] で元の値に戻せる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<long long> vals = a;                                   // 1. 値を集める
    sort(vals.begin(), vals.end());                               // 2. 並べる
    vals.erase(unique(vals.begin(), vals.end()), vals.end());     // 3. 重複を消す（erase まで書く）
    int k = vals.size();                                          // 番号は 0〜k-1

    vector<int> id(n);
    for (int i = 0; i < n; i++) {
        // a[i] より小さい異なる値の個数 ＝ a[i] の番号
        id[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) assert(vals[id[i]] == a[i]);  // 元の値に戻せる
    cout << k << '\n';
    for (int i = 0; i < n; i++) cout << id[i] << (i + 1 < n ? ' ' : '\n');
    if (n == 0) cout << '\n';
}
