#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    // --8<-- [start:core]
    for (int x : v | views::reverse) cout << x << ' ';  // 後ろから見るだけ
    cout << '\n';
    for (int x : v) cout << x << ' ';  // v はそのまま
    cout << '\n';
    ranges::reverse(v);  // v そのものを並べ替える（std::reverse(v.begin(), v.end()) と同じ）
    for (int x : v) cout << x << ' ';
    cout << '\n';
    // --8<-- [end:core]
}
