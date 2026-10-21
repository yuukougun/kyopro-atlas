// 各 i について、i から始まる区間の平均の最大 max_{r > i} (S_r − S_i)/(r − i) を、
// 累積和の点の上側凸包をスタックで保って求める（0-indexed、区間は [i, r)）。
// 入力：N と A_0 … A_{N−1}（|A_i| ≤ 10^6、N ≤ 2×10^5 を想定）。出力：各 i の最大の平均を既約分数「p/q」で。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
};
long long cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

// --8<-- [start:core]
// best[i] = 平均が最大になる区間 [i, r) の r（同じ平均なら長い方）
vector<int> max_average_end(const vector<long long>& a) {
    int n = a.size();
    vector<Point> P(n + 1);  // P[j] = (j, S_j)
    P[0] = {0, 0};
    for (int j = 0; j < n; j++) P[j + 1] = {j + 1, P[j].y + a[j]};
    vector<int> best(n);
    vector<int> st = {n};  // P[i+1..n] の上側凸包の頂点。末尾が左端（x が最小）
    for (int i = n - 1; i >= 0; i--) {
        // 末尾 t より 1 つ奥 u への傾きが大きいか等しい（u が t の左か一直線上）間は t を除く
        while (st.size() >= 2) {
            int t = st.back(), u = st[st.size() - 2];
            if (cross(P[t] - P[i], P[u] - P[i]) >= 0) st.pop_back();
            else break;
        }
        best[i] = st.back();  // P[i] の上側凸包の隣の頂点が、傾き（＝平均）を最大にする
        st.push_back(i);
    }
    return best;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<long long> s(n + 1, 0);
    for (int j = 0; j < n; j++) s[j + 1] = s[j] + a[j];
    vector<int> best = max_average_end(a);
    for (int i = 0; i < n; i++) {
        long long p = s[best[i]] - s[i], q = best[i] - i;
        long long g = gcd(llabs(p), q);
        cout << p / g << '/' << q / g << (i + 1 < n ? ' ' : '\n');
    }
    if (n == 0) cout << '\n';
}
