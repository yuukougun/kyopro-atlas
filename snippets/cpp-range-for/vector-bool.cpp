#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<bool> vb(n, true);
    for (auto&& b : vb) b = false;   // auto&& なら回せて、元が書き換わる
    // for (auto& b : vb)            // コンパイルエラー（vector-bool-ng.cpp）

    vb.assign(n, true);
    if (n >= 2) {
        auto y = vb[0];  // y は bool のコピーではなく、vb[0] を指す代わりの物
        y = false;       // vb[0] も false になる
        bool z = vb[1];  // 型を bool と書けばコピーになる
        z = !z;          // vb[1] は true のまま
        cout << z << '\n';
    }
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) cout << vb[i];
    cout << '\n';
}
