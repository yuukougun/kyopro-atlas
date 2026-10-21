#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {3, 1, 4, 1, 5, 3};
    // --8<-- [start:core]
    // C++17 までの書き方（erase(v, 3) と同じ意味）
    v.erase(remove(v.begin(), v.end(), 3), v.end());
    // --8<-- [end:core]
    for (int x : v) cout << x << ' ';
    cout << '\n';
}
