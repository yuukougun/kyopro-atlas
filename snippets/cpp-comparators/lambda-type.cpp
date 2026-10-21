#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto cmp = [](int x, int y) { return x > y; };
    set<int, decltype(cmp)> st;                          // C++20：cmp を渡さなくてよい
    priority_queue<int, vector<int>, decltype(cmp)> pq;  // 同上
    st.insert(1), st.insert(3);
    pq.push(1), pq.push(3);
    assert(*st.begin() == 3 && pq.top() == 1);
    // --8<-- [end:core]

    // --8<-- [start:capture]
    vector<int> w = {50, 10, 30};
    auto by_w = [&](int i, int j) { return w[i] < w[j]; };  // w をキャプチャする
    set<int, decltype(by_w)> idx(by_w);                      // C++20 でも by_w を渡す
    for (int i = 0; i < 3; i++) idx.insert(i);
    assert(*idx.begin() == 1);  // w が最小の添字
    // --8<-- [end:capture]
    cout << "ok\n";
}
