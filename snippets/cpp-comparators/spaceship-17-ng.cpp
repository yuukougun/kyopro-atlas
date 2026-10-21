#include <bits/stdc++.h>
using namespace std;

struct Edge {
    long long cost;
    int u, v;
    auto operator<=>(const Edge&) const = default;  // C++17 ではコンパイルエラー
};

int main() {
    vector<Edge> e = {{2, 0, 1}, {1, 1, 2}};
    sort(e.begin(), e.end());
}
