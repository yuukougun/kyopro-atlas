// 訪れた範囲の両端を状態にする：数直線の原点から出発し、速さ 1 で n 個の家（座標は 0 でなく互いに異なる）をすべて訪れる。
// 各家に初めて着いた時刻の和の最小を求める。
// 点（原点と家）を座標の順に並べ、dp[l][r][s] = 閉区間 [l, r] の点を訪れ終え、左端（s = 0）か右端（s = 1）にいるときの、
// 確定した時刻の和の最小（まだ訪れていない家が待った時間も先払いで含める）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long min_total_arrival(vector<long long> a) {
    int n = a.size();
    a.push_back(0);  // 出発点
    sort(a.begin(), a.end());
    int o = lower_bound(a.begin(), a.end(), 0LL) - a.begin();
    const long long INF = LLONG_MAX / 4;
    int k = n + 1;  // 点の数
    vector dp(k, vector(k, array<long long, 2>{INF, INF}));
    dp[o][o][0] = dp[o][o][1] = 0;  // 出発点は o 番目の点
    for (int len = 1; len < k; len++) {  // 訪れた点の数の小さい順（大きさ k の範囲からは広げない）
        for (int l = 0; l + len - 1 < k; l++) {
            int r = l + len - 1;
            int rem = k - len;  // まだ訪れていない家の数
            for (int s = 0; s < 2; s++) {
                long long cur = dp[l][r][s];
                if (cur >= INF) continue;
                long long x = (s == 0 ? a[l] : a[r]);
                // 1 歩分の移動の距離だけ、残りの家すべての着く時刻が遅れる
                if (l > 0) dp[l - 1][r][0] = min(dp[l - 1][r][0], cur + (x - a[l - 1]) * rem);
                if (r + 1 < k) dp[l][r + 1][1] = min(dp[l][r + 1][1], cur + (a[r + 1] - x) * rem);
            }
        }
    }
    return min(dp[0][k - 1][0], dp[0][k - 1][1]);
}
// --8<-- [end:core]

// 確かめ用：訪れる順を全通り試す
long long brute(vector<long long> a) {
    sort(a.begin(), a.end());
    long long best = LLONG_MAX;
    do {
        long long t = 0, pos = 0, sum = 0;
        for (long long x : a) {
            t += llabs(x - pos);
            pos = x;
            sum += t;
        }
        best = min(best, sum);
    } while (next_permutation(a.begin(), a.end()));
    return best;
}

int main() {
    mt19937 rng(1);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 6 + 1;
        set<long long> st;
        while ((int)st.size() < n) {
            long long x = (long long)(rng() % 21) - 10;
            if (x != 0) st.insert(x);
        }
        vector<long long> a(st.begin(), st.end());
        assert(min_total_arrival(a) == brute(a));
    }
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << min_total_arrival(a) << '\n';
}
