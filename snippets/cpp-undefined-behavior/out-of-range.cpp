#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, i;
    cin >> n >> i;
    // --8<-- [start:core]
    vector<int> a(n, 7);
    a[i] = 100;            // i == n なら範囲外への書き込み（未定義動作）
    cout << a[i] << '\n';  // 既定のビルドでは止まらず、100 と出て終わる
    // --8<-- [end:core]
}
