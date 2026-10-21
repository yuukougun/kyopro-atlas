// 辞書順最小の復元：各 i で a[i]（H）か b[i]（T）を選び和をちょうど s にする選び方のうち、
// H < T とした辞書順で最小の文字列を求める。後ろからの可否 DP を作り、前から貪欲に決める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    assert(n >= 1 && s >= 0);

    // --8<-- [start:core]
    // ok[i][j]：i 番目以降（i, …, n-1）の選び方で和を j にできるか
    vector ok(n + 1, vector<char>(s + 1, false));
    ok[n][0] = true;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= s; j++) {
            ok[i][j] = (j >= a[i] && ok[i + 1][j - a[i]]) || (j >= b[i] && ok[i + 1][j - b[i]]);
        }
    }
    if (!ok[0][s]) {
        cout << "No\n";
        return 0;
    }
    // 前から：小さい文字 H を置いても残りで達成できるなら H、だめなら T
    string ans;
    int j = s;  // 残りで作る和
    for (int i = 0; i < n; i++) {
        if (j >= a[i] && ok[i + 1][j - a[i]]) {
            ans += 'H';
            j -= a[i];
        } else {
            ans += 'T';
            j -= b[i];
        }
    }
    cout << ans << '\n';
    // --8<-- [end:core]
}
