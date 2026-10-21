#include <bits/stdc++.h>
using namespace std;

int main() {
    using P = pair<long long, int>;  // (距離, 頂点)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({5, 1});
    pq.push({7, 2});
    pq.push({9, 3});
    // --8<-- [start:core]
    const auto& [d, v] = pq.top();  // 先頭の要素を「参照」で受ける
    pq.pop();                       // 先頭の場所に別の要素が移ってくる
    cout << d << ' ' << v << '\n';  // 5 1 のつもりが 7 2 と出る
    // --8<-- [end:core]
}
