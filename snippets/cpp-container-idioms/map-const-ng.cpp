#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
int get(const map<int, int>& mp, int k) {
    return mp[k];  // コンパイルエラー：const の map には [] がない（要素を作るかもしれないため）
}
// --8<-- [end:core]

int main() {
    map<int, int> mp = {{1, 10}};
    cout << get(mp, 1) << '\n';
}
