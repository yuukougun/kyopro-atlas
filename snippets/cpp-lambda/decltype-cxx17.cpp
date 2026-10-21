#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto cmp = [](int x, int y) { return x > y; };
    set<int, decltype(cmp)> s(cmp);                          // C++17 ではラムダそのものも渡す
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    // --8<-- [end:core]
    for (int x : {3, 1, 4}) s.insert(x), pq.push(x);
    for (int x : s) cout << x << ' ';
    cout << pq.top() << '\n';
}
