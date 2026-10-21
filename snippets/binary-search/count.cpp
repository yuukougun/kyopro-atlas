#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    // --8<-- [start:core]
    sort(a.begin(), a.end());  // 二分探索の前に必ずソートする
    const long long INF = 4e18;
    vector<long long> b = a;  // 両端に番兵を置いた列（左右の最寄り用）
    b.insert(b.begin(), -INF);
    b.push_back(INF);
    // --8<-- [end:core]
    while (q--) {
        long long x;
        cin >> x;
        // --8<-- [start:query]
        long long lt = lower_bound(a.begin(), a.end(), x) - a.begin();  // x 未満の個数
        long long le = upper_bound(a.begin(), a.end(), x) - a.begin();  // x 以下の個数
        long long eq = le - lt;                                         // x に等しい個数
        auto it = lower_bound(b.begin(), b.end(), x);  // 番兵があるので必ず b の中を指す
        long long right = *it;        // x 以上で最小（右の最寄り。なければ INF）
        long long left = *prev(it);   // x 未満で最大（左の最寄り。なければ -INF）
        // --8<-- [end:query]
        cout << lt << ' ' << le << ' ' << eq << ' ';
        cout << (left == -INF ? string("-") : to_string(left)) << ' ';
        cout << (right == INF ? string("-") : to_string(right)) << '\n';
    }
}
