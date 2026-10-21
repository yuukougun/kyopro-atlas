#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v{3, 1, 4};
    // --8<-- [start:core]
    int best = 0;
    for (auto [i, x] : v | views::enumerate) {
        if (x >= 3) best = max(best, i);  // コンパイルエラー：int と ptrdiff_t
    }
    // --8<-- [end:core]
    cout << best << '\n';
}
