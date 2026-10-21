#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Edge {
    int to;
    long long cost;
    Edge(int t, long long c) : to(t), cost(c) {}   // コンストラクタを書くと集成体でなくなる
};
// --8<-- [end:core]

int main() {
    Edge e{.to = 1, .cost = 2};   // コンパイルエラー
    cout << e.to << '\n';
}
