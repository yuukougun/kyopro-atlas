#include <bits/stdc++.h>
using namespace std;

vector<int> make(int n) { return vector<int>(n, 1); }

int main() {
    int n;
    cin >> n;
    vector<int> v(n, 0);
    // --8<-- [start:core]
    auto&& a = v;        // 名前のある変数を受けると vector<int>&（v の別名）
    auto&& b = make(n);  // 一時オブジェクトを受けると vector<int>&&（寿命が b と同じに延びる）
    static_assert(is_same_v<decltype(a), vector<int>&>);
    static_assert(is_same_v<decltype(b), vector<int>&&>);
    // int& c = make(n)[0] は一時オブジェクトの中を指すので危ない。b なら安全に使える
    for (auto&& x : b) x *= 2;   // b の中身を書き換えられる
    // --8<-- [end:core]
    if (n > 0) a[0] = 5;
    cout << (n > 0 ? v[0] : -1) << ' ' << accumulate(b.begin(), b.end(), 0) << '\n';
}
