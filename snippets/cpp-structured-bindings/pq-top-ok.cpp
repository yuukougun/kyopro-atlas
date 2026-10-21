#include <bits/stdc++.h>
using namespace std;

int main() {
    using P = pair<long long, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({5, 1});
    pq.push({7, 2});
    pq.push({9, 3});
    // --8<-- [start:core]
    auto [d, v] = pq.top();  // 値で受ける（コピー）
    pq.pop();
    cout << d << ' ' << v << '\n';  // 5 1
    // --8<-- [end:core]
}
