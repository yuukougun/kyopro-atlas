#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;
    // --8<-- [start:core]
    size_t prev_cap = v.capacity();
    for (int i = 0; i < 20; i++) {
        v.push_back(i);
        if (v.capacity() != prev_cap) {  // 再確保が起きた
            cout << v.capacity() << ' ';
            prev_cap = v.capacity();
        }
    }
    cout << '\n';
    // --8<-- [end:core]
    // --8<-- [start:loop]
    vector<int> a = {1, 2, 3};
    for (int i = 0; i < (int)a.size(); i++) {   // 範囲 for ではなく添字で回す
        if (a[i] % 2 == 1 && a[i] < 10) a.push_back(a[i] * 10);  // a[i] は毎回読み直すので安全
    }
    // --8<-- [end:loop]
    for (int x : a) cout << x << ' ';
    cout << '\n';
    // --8<-- [start:set]
    set<int> st = {10, 20, 30};
    auto it = st.find(30);
    st.erase(20);            // 消した 20 以外のイテレータは使える
    st.insert(25);           // 挿入でも無効にならない
    cout << *it << ' ' << *prev(it) << '\n';  // 30 25
    // --8<-- [end:set]
}
