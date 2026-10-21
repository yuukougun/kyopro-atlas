// 後ろから決める：各 i について「i の倍数番目の b の和の偶奇が a[i]」となる 0/1 の列 b を作る
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<int> b(n + 1, 0);  // 1-indexed。b[i] は i 番目の箱に入れるか
    for (int i = n; i >= 1; i--) {  // 大きい i から決める
        int s = 0;
        for (int j = 2 * i; j <= n; j += i) s ^= b[j];  // 2i, 3i, … は決定済み
        b[i] = a[i] ^ s;  // 残る未知数は b[i] だけなので一意に決まる
    }
    // --8<-- [end:core]

    // 確かめ：すべての i で条件を満たす（合計 O(N log N)）
    for (int i = 1; i <= n; i++) {
        int s = 0;
        for (int j = i; j <= n; j += i) s ^= b[j];
        assert(s == a[i]);
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (b[i]) ans.push_back(i);
    cout << ans.size() << '\n';
    for (int k = 0; k < (int)ans.size(); k++) cout << ans[k] << (k + 1 < (int)ans.size() ? " " : "");
    cout << '\n';
}
