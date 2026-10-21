#include <bits/stdc++.h>
using namespace std;

int main() {
    map<int, int> mp = {{1, 10}};
    // --8<-- [start:core]
    if (mp[5] > 0) cout << "yes\n";      // 5 がないので mp[5] = 0 が作られる
    cout << mp.size() << '\n';           // 2（調べただけで要素が増えた）
    if (mp.contains(7) && mp.at(7) > 0) cout << "yes\n";  // 要素は増えない
    if (auto it = mp.find(1); it != mp.end()) cout << it->second << '\n';  // 10
    cout << mp.size() << '\n';           // 2
    try {
        cout << mp.at(9) << '\n';        // 9 はないので例外 out_of_range
    } catch (const out_of_range&) {
        cout << "out_of_range\n";
    }
    // --8<-- [end:core]
}
