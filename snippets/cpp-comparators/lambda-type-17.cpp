#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto cmp = [](int x, int y) { return x > y; };
    set<int, decltype(cmp)> st(cmp);                          // C++17 では cmp を渡す
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);  // 同上
    // --8<-- [end:core]
    st.insert(1), st.insert(3);
    pq.push(1), pq.push(3);
    assert(*st.begin() == 3 && pq.top() == 1);
    cout << "ok\n";
}
