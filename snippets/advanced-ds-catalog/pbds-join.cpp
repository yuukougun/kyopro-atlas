#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

int main() {
    // --8<-- [start:core]
    // 既定は pairing heap。greater で最小が先頭になる
    __gnu_pbds::priority_queue<int, greater<int>> a, b;
    for (int x : {5, 1, 9}) a.push(x);
    for (int x : {4, 2}) b.push(x);
    a.join(b);  // b の要素をすべて a に移す（b は空になる）
    // --8<-- [end:core]
    assert(b.empty() && a.size() == 5);
    while (!a.empty()) { cout << a.top() << ' '; a.pop(); }
    cout << '\n';
}
