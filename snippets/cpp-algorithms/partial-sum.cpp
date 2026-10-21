#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    vector<long long> s(n + 1, 0);  // s[0] = 0、s[i + 1] = s[i] + a[i]
    inclusive_scan(a.begin(), a.end(), s.begin() + 1, plus<>(), 0LL);  // 0LL の型で足す
    for (long long x : s) cout << x << ' ';
    cout << '\n';

    vector<long long> d(n);
    adjacent_difference(s.begin() + 1, s.end(), d.begin());  // d[0] = s[1]、d[i] = s[i + 1] - s[i]
    for (long long x : d) cout << x << ' ';                  // a に戻る
    cout << '\n';
    // --8<-- [end:core]

    // --8<-- [start:ng]
    vector<long long> t(n + 1, 0);
    partial_sum(a.begin(), a.end(), t.begin() + 1);  // 途中の和を a の要素の型 int で持つ
    // --8<-- [end:ng]
    for (long long x : t) cout << x << ' ';
    cout << '\n';
}
