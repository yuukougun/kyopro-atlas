#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost;
};

int main() {
    vector<Edge> es;
    // --8<-- [start:core]
    es.emplace_back(1, 10LL);   // -std=gnu++17 ではコンパイルエラー
    // --8<-- [end:core]
    cout << es.size() << '\n';
}
