#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    unordered_map<pair<int, int>, int> mp;  // コンパイルエラー：hash<pair<int, int>> がない
    // --8<-- [end:core]
    mp[{1, 2}] = 3;
    cout << mp.size() << '\n';
}
