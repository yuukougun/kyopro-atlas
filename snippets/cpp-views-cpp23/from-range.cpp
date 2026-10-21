#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    vector<int> r(from_range, a | views::reverse);     // 範囲から作る
    set<int> st;
    st.insert_range(a);                                // 範囲の要素をすべて入れる
    vector<int> b{0};
    b.append_range(a | views::take(2));                // 末尾に範囲を足す
    // --8<-- [end:core]
    for (int x : r) cout << x << ' ';
    cout << '\n' << st.size() << ' ' << b.size() << '\n';
}
