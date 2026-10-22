#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
};

int main() {
    int n;
    cin >> n;
    vector<P> ps(n);
    for (auto& [x, y] : ps) cin >> x >> y;
    // --8<-- [start:core]
    sort(ps.begin(), ps.end());  // P に比べ方がない
    // --8<-- [end:core]
    for (auto [x, y] : ps) cout << x << ' ' << y << '\n';
}
