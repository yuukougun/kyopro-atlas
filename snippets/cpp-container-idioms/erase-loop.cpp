#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> st;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        st.insert(a);
    }
    // --8<-- [start:core]
    for (auto it = st.begin(); it != st.end();) {
        if (*it % 2 == 0) it = st.erase(it);  // 消した要素の次を受け取る
        else ++it;                            // 消さないときだけ進める
    }
    // --8<-- [end:core]
    for (int x : st) cout << x << ' ';
    cout << '\n';
}
