#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // k 個ずつの塊の和（最後の塊は k 個未満のこともある）
    for (auto c : a | views::chunk(k)) cout << ranges::fold_left(c, 0LL, plus{}) << ' ';
    cout << '\n';
    // 長さ k の窓の和（n < k なら窓は 0 個）
    for (auto w : a | views::slide(k)) cout << ranges::fold_left(w, 0LL, plus{}) << ' ';
    cout << '\n';
    // 0 番目から k 個おき
    for (long long x : a | views::stride(k)) cout << x << ' ';
    cout << '\n';
    // --8<-- [end:core]
}
