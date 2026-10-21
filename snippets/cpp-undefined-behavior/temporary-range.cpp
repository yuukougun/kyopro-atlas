#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> groups(int n) {  // 偶数と奇数に分けて返す
    vector<vector<int>> g(2);
    for (int i = 0; i < n; i++) g[i % 2].push_back(i);
    return g;
}

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    // for (int v : groups(n)[0]) …  は C++20 までの規則ではダングリング（g++-13 と、g++-15 の -std=gnu++20）
    auto gs = groups(n);           // 変数に受けてから回せば、どの版でも安全
    for (int v : gs[0]) cout << v << ' ';
    cout << '\n';
    // --8<-- [end:core]
}
