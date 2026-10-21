// 部分区間も満たす型：値の種類数が k 以下の区間 [l, r) の個数を数える（空区間は数えない）。
// 右端 r を 1 つずつ進め、条件を破ったら左端 l を進めて直す。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) assert(0 <= a[i] && a[i] <= 1000000);

    // --8<-- [start:core]
    vector<int> cnt(1000001, 0);  // cnt[v]：区間 [l, r] に v が何個あるか
    int kinds = 0;                // 区間の値の種類数
    long long ans = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (cnt[a[r]]++ == 0) kinds++;  // a[r] を区間に入れる（0 個から 1 個になったら種類が増える）
        while (kinds > k) {             // 条件を破っている間、左端を縮める
            if (--cnt[a[l]] == 0) kinds--;  // 1 個から 0 個になったときだけ種類が減る
            l++;
        }
        ans += r - l + 1;  // 右端が r の区間のうち条件を満たすのは、左端が l, l+1, …, r のもの
    }
    // --8<-- [end:core]
    cout << ans << '\n';
}
