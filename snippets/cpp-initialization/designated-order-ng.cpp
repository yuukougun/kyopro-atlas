#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost = 1;
};

int main() {
    // --8<-- [start:core]
    Edge e{.cost = 5, .to = 3};   // 宣言順（to → cost）と逆なのでコンパイルエラー
    // --8<-- [end:core]
    cout << e.to << '\n';
}
