#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> d = {30, 10, 20};
    // --8<-- [start:core]
    // d[v] の小さい頂点から取り出す。d を参照するのでキャプチャが要る
    auto cmp = [&](int u, int v) { return d[u] > d[v]; };
    priority_queue<int, vector<int>, decltype(cmp)> pq;  // コンパイルエラー
    // --8<-- [end:core]
    for (int v = 0; v < 3; v++) pq.push(v);
    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << '\n';
}
