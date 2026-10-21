#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    set<int> st(v.begin(), v.end());
    map<int, int> cnt;
    for (int x : v) cnt[x]++;
    // --8<-- [start:core]
    size_t a = erase(v, 3);                                       // 3 をすべて消す
    size_t b = erase_if(st, [](int x) { return x % 2 == 0; });    // 偶数を消す（set）
    size_t c = erase_if(cnt, [](const auto& p) { return p.second == 1; });  // 1 回だけの値を消す（map）
    // --8<-- [end:core]
    cout << a << ' ' << b << ' ' << c << '\n';
    cout << v.size() << ' ' << st.size() << ' ' << cnt.size() << '\n';
}
