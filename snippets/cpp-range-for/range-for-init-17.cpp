#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {5, 6, 7};
    // --8<-- [start:core]
    for (int i = 0; auto x : a) {  // -std=gnu++17 では警告（C++20 の機能）
        cout << i << ':' << x << ' ';
        i++;
    }
    // --8<-- [end:core]
    cout << '\n';
}
