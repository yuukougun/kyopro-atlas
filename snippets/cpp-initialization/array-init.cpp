#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int n;
    cin >> s >> n;
    // --8<-- [start:core]
    array<int, 26> cnt{};          // {} で 26 個とも 0
    for (char ch : s) cnt[ch - 'a']++;
    vector<array<int, 3>> v(n);    // n 個の array。中身はすべて 0
    // --8<-- [end:core]
    // --8<-- [start:partial]
    int a[5] = {-1};               // -1, 0, 0, 0, 0（全部が -1 にはならない）
    array<int, 3> b{1};            // 1, 0, 0
    // --8<-- [end:partial]
    cout << cnt['a' - 'a'] << ' ' << cnt['z' - 'a'] << ' ' << v.size() << '\n';
    for (auto& x : v) assert(x[0] == 0 && x[1] == 0 && x[2] == 0);
    cout << a[0] << ' ' << a[4] << ' ' << b[0] << ' ' << b[2] << '\n';
}
