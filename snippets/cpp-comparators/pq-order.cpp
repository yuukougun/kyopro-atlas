#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {3, 1, 4, 1, 5};
    // --8<-- [start:core]
    priority_queue<int> mx;                                // 既定（less）：最大が top
    priority_queue<int, vector<int>, greater<int>> mn;     // greater：最小が top
    for (int x : a) mx.push(x), mn.push(x);
    assert(mx.top() == 5 && mn.top() == 1);

    auto cmp = [](int x, int y) { return x > y; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);  // 最小が top
    for (int x : a) pq.push(x);
    assert(pq.top() == 1);

    vector<int> b = a;
    sort(b.begin(), b.end(), cmp);  // 同じ cmp を sort に渡すと降順：{5, 4, 3, 1, 1}
    assert(b.front() == 5);
    // --8<-- [end:core]

    // --8<-- [start:dijkstra]
    // ダイクストラ法のキュー：(距離, 頂点) の距離が小さい順に取り出す
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> que;
    que.emplace(7, 0);
    que.emplace(2, 1);
    que.emplace(2, 0);
    auto [d, v] = que.top();  // (2, 0)：距離が等しければ頂点の小さい方
    // --8<-- [end:dijkstra]
    assert(d == 2 && v == 0);
    cout << "ok\n";
}
