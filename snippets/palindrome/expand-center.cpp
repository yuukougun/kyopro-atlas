// 中心から伸ばす：文字列 s の部分文字列のうち、対称な位置の不一致が k 組以下のものを数える。
// k = 0 なら回文の部分文字列の個数。中心は 2N − 1 個（文字の上 N 個と文字の間 N − 1 個）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    string s;
    cin >> k >> s;
    int n = s.size();
    assert(k >= 0);

    // --8<-- [start:core]
    long long count = 0;
    // c = l + r（閉区間 [l, r] の両端の和）が中心を表す。c が偶数なら文字の上、奇数なら文字の間
    for (int c = 0; c <= 2 * (n - 1); c++) {
        int l = c / 2, r = c - c / 2;  // 最初の 1 組（奇数長なら l == r で 1 文字）
        int mismatch = 0;
        while (0 <= l && r < n) {
            if (s[l] != s[r]) mismatch++;
            if (mismatch > k) break;  // 外側に伸ばしても不一致は減らない
            count++;                  // s[l, r] は条件を満たす
            l--;
            r++;
        }
    }
    cout << count << '\n';
    // --8<-- [end:core]
}
