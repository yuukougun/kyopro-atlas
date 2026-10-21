#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Edge {
    int to;
    long long cost = 1;   // 既定値
};
// --8<-- [end:core]

int main() {
    int v;
    long long c;
    cin >> v >> c;
    // --8<-- [start:use]
    Edge e1{v, c};                 // 宣言順に並べる
    Edge e2{.to = v, .cost = c};   // 名前を書く（C++20）
    Edge e3{.to = v};              // 書かないメンバは既定値 1
    // --8<-- [end:use]
    cout << e1.to << ' ' << e1.cost << ' ' << e2.to << ' ' << e2.cost << ' ' << e3.to << ' ' << e3.cost << '\n';
}
