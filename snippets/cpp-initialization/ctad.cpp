#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    vector dp(n, vector(m, 0LL));   // vector<vector<long long>>
    vector bad(n, vector(m, 0));    // vector<vector<int>>（0 は int）
    vector d3(n, vector(m, vector(2, -1)));  // 3 次元。中身は int
    static_assert(is_same_v<decltype(dp), vector<vector<long long>>>);
    static_assert(is_same_v<decltype(bad), vector<vector<int>>>);
    static_assert(is_same_v<decltype(d3), vector<vector<vector<int>>>>);
    // --8<-- [end:core]
    cout << dp.size() << ' ' << (n > 0 ? dp[0].size() : 0) << ' ' << d3.size() << '\n';
}
