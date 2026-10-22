// CHT（傾きもクエリも単調）：dp[i] = min_{j<i} (dp[j] + (h_i - h_j)^2) + C を O(N) で求める
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 直線 y = a x + b の最小値。傾き a は単調減少（同じでもよい）、クエリの x は単調増加で来る
struct MonotoneCHT {
    deque<pair<long long, long long>> q;  // (a, b)。先頭ほど傾きが大きい
    static long long eval(const pair<long long, long long>& f, long long x) {
        return f.first * x + f.second;
    }
    // 真ん中の g が不要か：f と h の交点が、f と g の交点より左（同じ位置）にある
    static bool unneeded(const pair<long long, long long>& f, const pair<long long, long long>& g,
                         const pair<long long, long long>& h) {
        // (h.b - f.b) / (f.a - h.a) <= (g.b - f.b) / (f.a - g.a) を、割らずに掛けて比べる
        return (__int128)(h.second - f.second) * (f.first - g.first) <=
               (__int128)(g.second - f.second) * (f.first - h.first);
    }
    void add(long long a, long long b) {
        pair<long long, long long> h{a, b};
        if (!q.empty() && q.back().first == a) {      // 同じ傾きは切片の小さい方だけ残す
            if (q.back().second <= b) return;
            q.pop_back();
        }
        while (q.size() >= 2 && unneeded(q[q.size() - 2], q.back(), h)) q.pop_back();
        q.push_back(h);
    }
    long long query(long long x) {                    // x は前回以上
        while (q.size() >= 2 && eval(q[0], x) >= eval(q[1], x)) q.pop_front();
        return eval(q[0], x);
    }
};
// --8<-- [end:core]

vector<long long> solve(const vector<long long>& h, long long c) {
    int n = h.size();
    vector<long long> dp(n, 0);
    MonotoneCHT cht;
    cht.add(-2 * h[0], dp[0] + h[0] * h[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = cht.query(h[i]) + h[i] * h[i] + c;
        cht.add(-2 * h[i], dp[i] + h[i] * h[i]);
    }
    return dp;
}

vector<long long> naive(const vector<long long>& h, long long c) {
    int n = h.size();
    vector<long long> dp(n, LLONG_MAX);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++) dp[i] = min(dp[i], dp[j] + (h[i] - h[j]) * (h[i] - h[j]) + c);
    return dp;
}

int main() {
    // 乱数で愚直な O(N^2) と比べる（h は狭義単調増加）
    mt19937 rng(1);
    for (int t = 0; t < 300; t++) {
        int n = rng() % 30 + 1;
        vector<long long> h(n);
        long long cur = 0;
        for (auto& x : h) x = (cur += rng() % 20 + 1);
        long long c = rng() % 200;
        assert(solve(h, c) == naive(h, c));
    }
    int n;
    long long c;
    cin >> n >> c;
    vector<long long> h(n);
    for (auto& x : h) cin >> x;
    cout << solve(h, c).back() << '\n';
}
