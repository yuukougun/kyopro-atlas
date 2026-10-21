#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    set<int> st = {10, 20, 30, 40};
    // --8<-- [start:core]
    cout << *st.begin() << ' ' << *prev(st.end()) << ' ' << *st.rbegin() << '\n';  // 10 40 40
    auto it = st.lower_bound(x);                    // x 以上で最小の要素
    if (it != st.end()) cout << "ge " << *it << '\n';
    if (it != st.begin()) cout << "lt " << *prev(it) << '\n';  // x 未満で最大の要素
    if (it != st.end() && next(it) != st.end()) cout << "next " << *next(it) << '\n';
    // --8<-- [end:core]
}
