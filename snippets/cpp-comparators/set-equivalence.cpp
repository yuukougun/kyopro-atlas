#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto by_second = [](const pair<int, int>& p, const pair<int, int>& q) {
        return p.second < q.second;
    };
    set<pair<int, int>, decltype(by_second)> st;
    st.insert({1, 5});
    st.insert({2, 5});  // !by_second(a, b) && !by_second(b, a) なので {1, 5} と「同じ」で、入らない
    assert(st.size() == 1);
    assert(st.count({9, 5}) == 1);  // second が 5 なら何でも「ある」と答える

    // second で比べ、等しければ first で比べる
    auto by_second_then_first = [](const pair<int, int>& p, const pair<int, int>& q) {
        return pair(p.second, p.first) < pair(q.second, q.first);
    };
    set<pair<int, int>, decltype(by_second_then_first)> st2;
    st2.insert({1, 5});
    st2.insert({2, 5});
    assert(st2.size() == 2);
    // --8<-- [end:core]
    cout << "ok\n";
}
