#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 2, m = 3;
    // --8<-- [start:core]
    vector<vector<long long>> dp(n, vector<int>(m));   // 内側の型が違うのでコンパイルエラー
    // --8<-- [end:core]
    cout << dp.size() << '\n';
}
