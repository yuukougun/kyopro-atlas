#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    map<int, int> first_pos;  // 値 → 最初に出た位置
    set<int> seen;
    for (int i = 0; i < n; i++) {
        if (auto [it, ok] = seen.insert(a[i]); ok) {  // 新しく入ったときだけ ok が true
            first_pos[a[i]] = i;
        }
    }
    int k;
    cin >> k;
    if (auto it = first_pos.find(k); it != first_pos.end()) {
        cout << it->second << '\n';
    } else {
        cout << -1 << '\n';  // it は else の中でも使える。if 文の外では使えない
    }
    // --8<-- [end:core]
}
