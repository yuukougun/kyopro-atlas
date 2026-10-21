#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

// --8<-- [start:core]
// dp[s]：いま箱にある要素から選んで、和を s にする選び方の数（mod 998244353）
// 追加：0-1 ナップサックと同じく、和の大きい方から足す
void add(vector<long long>& dp, int x) {
    int k = (int)dp.size() - 1;
    for (int s = k; s >= x; s--) dp[s] = (dp[s] + dp[s - x]) % MOD;
}

// 削除：追加の逆。和の小さい方から引く（dp[s - x] は先に元へ戻っている）
void remove(vector<long long>& dp, int x) {
    int k = (int)dp.size() - 1;
    for (int s = x; s <= k; s++) dp[s] = (dp[s] - dp[s - x] + MOD) % MOD;
}
// --8<-- [end:core]

int main() {
    int q, k;
    cin >> q >> k;
    vector<long long> dp(k + 1, 0);
    dp[0] = 1;  // 何も選ばない選び方が 1 通り
    multiset<int> box;
    for (int i = 0; i < q; i++) {
        char c;
        int x;
        cin >> c >> x;
        assert(x >= 1);  // x = 0 は引き算では戻せない（落とし穴を参照）
        if (c == '+') {
            add(dp, x);
            box.insert(x);
        } else {
            assert(box.count(x));  // 箱にない値は取り出せない
            remove(dp, x);
            box.erase(box.find(x));
        }
        cout << dp[k] << '\n';
    }
    // 最後の dp が、残った要素で作り直した表と一致することを確かめる
    vector<long long> fresh(k + 1, 0);
    fresh[0] = 1;
    for (int x : box) add(fresh, x);
    assert(fresh == dp);
}
