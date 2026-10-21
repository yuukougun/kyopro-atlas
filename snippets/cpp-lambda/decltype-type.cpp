#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto cmp = [](int x, int y) { return x > y; };  // キャプチャのないラムダ
    set<int, decltype(cmp)> s = {3, 1, 4};           // 大きい順に並ぶ
    priority_queue<int, vector<int>, decltype(cmp)> pq;  // x > y を渡すので top は最小
    for (int x : {3, 1, 4}) pq.push(x);
    // --8<-- [end:core]
    for (int x : s) cout << x << ' ';
    cout << pq.top() << '\n';
}
