#include <bits/stdc++.h>
using namespace std;

int main() {
    using P = pair<long long, int>;  // (距離, 頂点)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({5, 1});
    pq.push({7, 2});
    // --8<-- [start:core]
    const auto& [d, v] = pq.top();  // 先頭の場所を指す参照
    pq.pop();                       // 先頭の場所に (7, 2) が移ってくる
    cout << d << ' ' << v << '\n';  // 5 1 のつもりが 7 2 と出る
    // --8<-- [end:core]
}
