#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    vector<long long> a = {1000000000, 1000000000, 1000000000};
    cout << accumulate(a.begin(), a.end(), 0) << '\n';    // int で足す：-1294967296
    cout << accumulate(a.begin(), a.end(), 0LL) << '\n';  // 3000000000
    cout << reduce(a.begin(), a.end()) << '\n';           // 初期値を省くと long long{} から：3000000000

    vector<double> d = {0.5, 0.5, 0.5};
    cout << accumulate(d.begin(), d.end(), 0) << '\n';    // 毎回 int に切り捨てる：0
    cout << accumulate(d.begin(), d.end(), 0.0) << '\n';  // 1.5
    // --8<-- [end:core]

    assert(accumulate(a.begin(), a.end(), 0LL) == 3000000000LL);
    vector<int> e;
    cout << accumulate(e.begin(), e.end(), 0) << '\n';  // 空なら初期値そのもの
}
