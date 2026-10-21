#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto print = [](const vector<int>& v) {
        for (int x : v) cout << x << ' ';
        cout << '\n';
    };
    // --8<-- [start:core]
    sort(a.begin(), a.end());               // 昇順
    print(a);
    sort(a.begin(), a.end(), greater<>());  // 降順（比較関数を渡す）
    print(a);
    sort(a.rbegin(), a.rend());             // 逆向きのイテレータで昇順に並べる＝降順
    print(a);
    // --8<-- [end:core]
}
