#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    vector<int> v = {10, 20, 20, 30};
    set<int> st(v.begin(), v.end());
    // --8<-- [start:core]
    int i = lower_bound(v.begin(), v.end(), x) - v.begin();  // x 以上の最初の添字（なければ v.size()）
    int k = upper_bound(v.begin(), v.end(), x) - v.begin();  // x より大きい最初の添字
    cout << i << ' ' << k - i << '\n';                       // 添字と、x の個数
    auto d = distance(st.begin(), st.lower_bound(x));        // set でも書けるが O(N)
    cout << d << '\n';
    // --8<-- [end:core]
}
