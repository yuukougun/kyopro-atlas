#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];  // 最後だけ改行、ほかは空白
    bool ok = n > 0 && a[0] == a[n - 1];
    cout << (ok ? "Yes" : "No") << '\n';  // << より優先順位が低いので、かっこが要る
    // --8<-- [end:core]
}
