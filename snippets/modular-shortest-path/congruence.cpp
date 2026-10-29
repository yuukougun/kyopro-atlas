#include <bits/stdc++.h>
using namespace std;

// 正の整数 a_1, ..., a_n の非負整数結合（a_1 x_1 + ... + a_n x_n、x_i ≥ 0）で作れる数を調べる。
// --8<-- [start:core]
const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

// d[r]：作れる数のうち、m = min(a) で割った余りが r の最小値（作れなければ INF）
vector<long long> min_by_residue(const vector<long long>& a) {
    long long m = *min_element(a.begin(), a.end());
    vector<long long> d(m, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    d[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [dv, r] = pq.top();
        pq.pop();
        if (dv > d[r]) continue;
        for (long long x : a) {
            int s = (r + x) % m;  // 辺 r → (r + x) mod m、重み x
            if (s == r) continue;  // x が m の倍数なら自己ループ
            if (dv + x < d[s]) {
                d[s] = dv + x;
                pq.push({d[s], s});
            }
        }
    }
    return d;
}

// 閉区間 [0, h] で作れる数の個数：d[r] 以上で余り r の数は d[r] + km ですべて作れる
long long count_upto(const vector<long long>& d, long long h) {
    long long m = d.size(), cnt = 0;
    for (long long r = 0; r < m; r++) {
        if (d[r] != INF && d[r] <= h) cnt += (h - d[r]) / m + 1;  // 作れない余りは H が大きくても数えない
    }
    return cnt;
}
// --8<-- [end:core]

// 愚直：[0, h] の各数を作れるかを個数制限なしのナップサックで調べる
long long brute(const vector<long long>& a, long long h) {
    vector<bool> ok(h + 1, false);
    ok[0] = true;
    for (long long v = 1; v <= h; v++) {
        for (long long x : a) {
            if (x <= v && ok[v - x]) ok[v] = true;
        }
    }
    return count(ok.begin(), ok.end(), true);
}

int main() {
    int n;
    long long h;
    cin >> n >> h;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    vector<long long> d = min_by_residue(a);
    for (long long t = 0; t <= min(h, 3000LL); t++) assert(count_upto(d, t) == brute(a, t));

    // 作れない最大の数は max d[r] − m（d に INF があれば、作れない数は無限にある）
    long long mx = *max_element(d.begin(), d.end());
    cout << count_upto(d, h) << '\n';
    if (mx == INF) {
        cout << "INF" << '\n';
    } else {
        cout << mx - (long long)d.size() << '\n';
    }
}
