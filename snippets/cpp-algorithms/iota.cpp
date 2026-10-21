#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);  // idx = {0, 1, ..., n - 1}（C++23 なら ranges::iota(idx, 0)）
    stable_sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    for (int i : idx) cout << i << ' ';  // a の小さい順に並べた添字
    cout << '\n';
    // --8<-- [end:core]
}
