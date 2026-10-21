#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++) cin >> wt[i] >> val[i];
    // --8<-- [start:core]
    // 0-1 ナップサックの dp を 2 本の配列で回す
    vector<long long> dp(w + 1, 0), ndp(w + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= w; j++) {
            ndp[j] = dp[j];
            if (j >= wt[i]) ndp[j] = max(ndp[j], dp[j - wt[i]] + val[i]);
        }
        swap(dp, ndp);  // 中身の置き場所を入れ替えるだけ：O(1)
        // dp = ndp;    // こちらは w + 1 個をコピーする：O(W)
    }
    // --8<-- [end:core]
    cout << dp[w] << '\n';

    // --8<-- [start:move]
    vector<int> a = {1, 2, 3};
    vector<int> b = move(a);  // 中身を b に移す（コピーしない）
    // 手元では a.size() == 0。移した後の a は、代入し直すまで中身を当てにしない
    a = {9};                  // 代入し直せば普通に使える
    // --8<-- [end:move]
    cout << b.size() << ' ' << a.size() << '\n';
}
