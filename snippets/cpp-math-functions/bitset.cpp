#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100000;  // 大きさはコンパイル時の定数。制約の最大値から決める

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> w(n);
    for (auto& x : w) cin >> x;
    // --8<-- [start:core]
    bitset<MAXS + 1> dp;      // dp[s]：和 s が作れるか
    dp[0] = 1;
    for (int x : w) dp |= dp << x;  // 全部の s を 64 個ずつまとめて更新する
    int cnt = dp.count();           // 作れる和の個数（1 の個数）
    vector<int> sums;               // 作れる和を小さい順に（GCC の拡張）
    for (int s = dp._Find_first(); s <= MAXS; s = dp._Find_next(s)) sums.push_back(s);
    // --8<-- [end:core]
    cout << (dp[t] ? "Yes" : "No") << ' ' << cnt << '\n';
    for (int s : sums) cout << s << ' ';
    cout << '\n';
}
