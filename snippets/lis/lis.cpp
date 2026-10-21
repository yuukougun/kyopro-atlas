// 最長増加部分列の長さを二分探索版で求める。狭義（a_i < a_j）と広義（a_i <= a_j）の両方を出す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// L[k] は「長さ k + 1 の増加部分列の末尾として取りうる最小値」。L は常に昇順に並ぶ
int lis_length(const vector<long long>& a, bool strict) {
    vector<long long> L;
    for (long long x : a) {
        // 狭義なら x 以上の最初の位置、広義なら x より大きい最初の位置を x で置き換える
        auto it = strict ? lower_bound(L.begin(), L.end(), x) : upper_bound(L.begin(), L.end(), x);
        if (it == L.end()) L.push_back(x);  // どの長さの末尾よりも大きい：最長が 1 延びる
        else *it = x;                       // 同じ長さの列の末尾を小さくする
    }
    return (int)L.size();
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    assert(n >= 0);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << lis_length(a, true) << ' ' << lis_length(a, false) << '\n';
}
