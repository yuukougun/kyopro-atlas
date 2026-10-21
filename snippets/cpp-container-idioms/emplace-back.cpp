#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    vector<pair<int, int>> e;
    e.emplace_back(1, 2);         // 引数から pair をその場で作る
    e.push_back({3, 4});          // {} で pair を作って渡す。結果は同じ
    vector<vector<int>> vs;
    vs.emplace_back(3);           // vector<int>(3)、すなわち {0, 0, 0} を足す
    vs.push_back({3});            // 要素 1 個の {3} を足す
    // --8<-- [end:core]
    cout << e[0].first << e[0].second << e[1].first << e[1].second << '\n';
    cout << vs[0].size() << ' ' << vs[1].size() << ' ' << vs[1][0] << '\n';
}
