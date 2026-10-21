#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost = 1;
};

int main() {
    Edge e{.to = 3, .cost = 5};   // -std=c++17 -Wpedantic では警告（GCC の拡張として通る）
    cout << e.to << ' ' << e.cost << '\n';
}
