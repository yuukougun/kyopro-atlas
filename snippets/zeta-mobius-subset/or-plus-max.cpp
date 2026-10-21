// 長さ 2^n の列 a について、各 K = 1..2^n-1 で、i < j かつ (i OR j) ≤ K を満たす a_i + a_j の最大値を求める。
// 部分集合ごとに「部分集合の中の上位 2 つ（添字が異なる）」を高速ゼータ変換の形で集め、K について累積の max を取る。
// main の中で、愚直な O(4^n) の計算と一致することを assert で確かめる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// --8<-- [start:top2]
const long long NEG = LLONG_MIN / 4;  // 「まだない」を表す番兵（足しても溢れない）

// 上位 2 つ (first ≥ second) に、もう 1 組の上位 2 つを合わせる
pair<long long, long long> merge_top2(pair<long long, long long> x, pair<long long, long long> y) {
    long long c[4] = {x.first, x.second, y.first, y.second};
    sort(c, c + 4, greater<long long>());
    return {c[0], c[1]};
}

// top[S] は S の部分集合の添字の中で a の値が大きい 2 つ（添字は異なる）
vector<pair<long long, long long>> top2_zeta(const vector<long long>& a, int n) {
    vector<pair<long long, long long>> top(1 << n);
    for (int s = 0; s < (1 << n); s++) top[s] = {a[s], NEG};
    for (int i = 0; i < n; i++)
        for (int s = 0; s < (1 << n); s++)
            if (s >> i & 1) top[s] = merge_top2(top[s], top[s ^ (1 << i)]);
    return top;
}
// --8<-- [end:top2]

// --8<-- [start:answer]
vector<long long> or_plus_max(const vector<long long>& a, int n) {
    vector<pair<long long, long long>> top = top2_zeta(a, n);
    // K 以下のすべての S（S ≥ 1）で max を取る
    vector<long long> ans(1 << n, NEG);
    long long best = NEG;
    for (int k = 1; k < (1 << n); k++) {
        best = max(best, top[k].first + top[k].second);
        ans[k] = best;
    }
    return ans;
}
// --8<-- [end:answer]
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(1 << n);
    for (auto& x : a) cin >> x;
    vector<long long> ans = or_plus_max(a, n);
    for (int k = 1; k < (1 << n); k++) {
        long long naive = NEG;
        for (int i = 0; i < (1 << n); i++)
            for (int j = i + 1; j < (1 << n); j++)
                if ((i | j) <= k) naive = max(naive, a[i] + a[j]);
        assert(ans[k] == naive);
        cout << ans[k] << '\n';
    }
}
