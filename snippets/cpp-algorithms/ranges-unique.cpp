#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    ranges::sort(v);
    auto tail = ranges::unique(v);   // 後ろの不要部分 [新しい終端, v.end()) を表す subrange
    cout << tail.size() << '\n';     // 消える要素の数
    v.erase(tail.begin(), v.end());  // tail.end() は v.end() と同じ
    // --8<-- [end:core]
    for (int x : v) cout << x << ' ';
    cout << '\n';
}
