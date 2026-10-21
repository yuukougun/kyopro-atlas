#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    for (int x : a) {
        if (x % 2 != 0) continue;  // filter
        int y = x * x;             // transform
        cout << y << ' ';
    }
    cout << '\n';
    // --8<-- [end:core]
}
