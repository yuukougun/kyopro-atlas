// 0 と 1 の列 s に区間の反転を k 回まで行い、連続する 1 の長さを最大にする。
// 1 の塊・0 の塊が交互に並び、1 の塊で始まって 1 の塊で終わるように長さ 0 の塊を補い、
// 0 の塊 k 個とその両側の 1 の塊（塊 2k + 1 個）の窓を塊の列で動かす。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    assert((int)s.size() == n && k >= 1);

    // --8<-- [start:core]
    // len[0], len[2], … が 1 の塊、len[1], len[3], … が 0 の塊の長さ
    vector<int> len;
    if (s[0] == '0') len.push_back(0);  // 先頭が 0 なら長さ 0 の 1 の塊を補う
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        len.push_back(j - i);
        i = j;
    }
    if (s[n - 1] == '0') len.push_back(0);  // 末尾が 0 なら長さ 0 の 1 の塊を補う
    int m = len.size();  // 奇数で、1 の塊が (m + 1) / 2 個

    // 偶数番目（1 の塊）から始まる、塊 2k + 1 個までの窓の長さの最大
    int best = 0, sum = 0, right = 0;
    for (int left = 0; left < m; left += 2) {
        int end = min(m, left + 2 * k + 1);
        while (right < end) sum += len[right++];  // 右端は戻らない
        best = max(best, sum);
        sum -= len[left];  // 左端を塊 2 個分進める
        if (left + 1 < m) sum -= len[left + 1];
    }
    cout << best << '\n';
    // --8<-- [end:core]
}
