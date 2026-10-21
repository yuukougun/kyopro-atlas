// 平面走査と BIT：重み付きの点の、長方形 [l, r) × [d, u) の中の重みの和（オフライン）
// 入力：N Q、続く N 行に x y w、続く Q 行に l d r u。各クエリの答えを 1 行ずつ出力
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

// --8<-- [start:core]
struct Point { long long x, y, w; };
struct Query { long long l, d, r, u; };  // [l, r) × [d, u)

vector<long long> rectangle_sum(vector<Point> ps, const vector<Query>& qs) {
    // y を座標圧縮する（BIT の添字にする）
    vector<long long> ys;
    for (auto& p : ps) ys.push_back(p.y);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto yid = [&](long long y) { return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()); };

    // 長方形の和 =（x < r の点の、y が [d, u) の和）−（x < l の点の、同じ和）
    struct Ev { long long x; int qi, sign; };
    vector<Ev> evs;
    for (int i = 0; i < (int)qs.size(); i++) {
        evs.push_back({qs[i].r, i, +1});
        evs.push_back({qs[i].l, i, -1});
    }
    sort(ps.begin(), ps.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
    sort(evs.begin(), evs.end(), [](const Ev& a, const Ev& b) { return a.x < b.x; });

    atcoder::fenwick_tree<long long> bit(ys.size());
    vector<long long> ans(qs.size(), 0);
    int j = 0;
    for (auto& e : evs) {
        // 走査線を x = e.x の直前まで進める：x < e.x の点だけを入れる
        while (j < (int)ps.size() && ps[j].x < e.x) {
            bit.add(yid(ps[j].y), ps[j].w);
            j++;
        }
        const Query& q = qs[e.qi];
        ans[e.qi] += e.sign * bit.sum(yid(q.d), yid(q.u));  // y が [d, u) の点
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<Point> ps(n);
    for (auto& p : ps) cin >> p.x >> p.y >> p.w;
    vector<Query> qs(q);
    for (auto& t : qs) cin >> t.l >> t.d >> t.r >> t.u;
    vector<long long> ans = rectangle_sum(ps, qs);
    // 素朴な数え上げと照らし合わせる
    for (int i = 0; i < q; i++) {
        long long s = 0;
        for (auto& p : ps) {
            if (qs[i].l <= p.x && p.x < qs[i].r && qs[i].d <= p.y && p.y < qs[i].u) s += p.w;
        }
        assert(s == ans[i]);
        cout << ans[i] << '\n';
    }
}
