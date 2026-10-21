#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Seg {
    int l, r;
    // 右端の小さい順。最後の const がないと set・priority_queue・ranges::sort で使えない
    bool operator<(const Seg& o) const { return r < o.r; }
};
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<Seg> v(n);
    for (auto& [l, r] : v) cin >> l >> r;
    sort(v.begin(), v.end());
    set<Seg> st(v.begin(), v.end());
    priority_queue<Seg> pq(v.begin(), v.end());  // 右端の最大が top
    for (auto& [l, r] : v) cout << l << ' ' << r << '\n';
    cout << st.size() << '\n';
    if (!pq.empty()) cout << pq.top().r << '\n';
}
