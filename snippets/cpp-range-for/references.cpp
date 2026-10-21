#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) g[i].push_back(i);
    // --8<-- [start:core]
    int x = 1;
    int& r = x;   // r は x の別名。箱は増えない
    r = 5;        // x も 5 になる
    int y = x;    // y はコピー。新しい箱
    y = 7;        // x は 5 のまま

    if (n > 0) {
        vector<int>& row = g[0];        // 書き換える別名（コピーしない）
        row.push_back(100);             // g[0] に入る
        const vector<int>& c = g[0];    // 読むだけの別名（コピーしない）
        // c.push_back(1);              // コンパイルエラー：const の参照からは書き換えられない
        cout << c.size() << '\n';
    }
    // --8<-- [end:core]
    cout << x << ' ' << y << '\n';
}
