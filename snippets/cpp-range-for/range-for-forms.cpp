#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<int> a(n);
    for (auto& x : a) cin >> x;            // 参照で受けて、a の各要素に読み込む

    for (auto x : a) x *= 2;               // x はコピー。a は変わらない
    for (auto& x : a) x += 1;              // x は a の要素の別名。a が変わる

    vector<string> s = {"abc", "de"};
    for (const auto& t : s) cout << t.size() << ' ';  // コピーせず読むだけ
    cout << '\n';
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? " " : "");
    cout << '\n';
}
