#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    set<int> st = {10, 20, 30};
    // --8<-- [start:core]
    auto it = st.lower_bound(x);                    // メンバ：O(log N)
    // auto it = lower_bound(st.begin(), st.end(), x);  // 結果は同じだが O(N)
    // auto it = ranges::lower_bound(st, x);            // これも O(N)
    if (it == st.end()) cout << "none\n";           // x 以上の要素がない
    else cout << *it << '\n';
    // --8<-- [end:core]
}
