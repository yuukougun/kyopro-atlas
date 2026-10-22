// Li Chao Tree：直線の追加と、x での最小値（Library Checker の line_add_get_min の入出力）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 問い合わせる x を先に集めて xs（ソート済み・重複なし）にしておく。各ノードは直線を高々 1 本持つ
struct LiChaoTree {
    struct Line { long long a, b; bool has; };
    int n;
    vector<long long> xs;
    vector<Line> t;
    LiChaoTree(vector<long long> xs_) : n(xs_.size()), xs(xs_), t(4 * max(n, 1), {0, 0, false}) {}
    static long long eval(const Line& f, long long x) { return f.a * x + f.b; }

    // ノード k が受け持つのは xs[l, r)。真ん中 xs[m] で勝つ方を残し、負けた方を半分へ押し下げる
    void add(Line f, int k, int l, int r) {
        if (!t[k].has) { t[k] = f; return; }
        int m = (l + r) / 2;
        bool left = eval(f, xs[l]) < eval(t[k], xs[l]);
        bool mid = eval(f, xs[m]) < eval(t[k], xs[m]);
        if (mid) swap(f, t[k]);          // t[k] は xs[m] で小さい方になる
        if (r - l == 1) return;
        if (left != mid) add(f, 2 * k, l, m);      // 負けた方は左端で勝つ：交点は [l, m) の側
        else add(f, 2 * k + 1, m, r);              // そうでなければ右の側でしか勝てない
    }
    void add(long long a, long long b) { add({a, b, true}, 1, 0, n); }

    // xs[i] を受け持つノードを根から葉へたどり、置かれた直線の最小を取る
    long long query(long long x) {
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();  // x は xs にある前提
        long long res = LLONG_MAX;
        int k = 1, l = 0, r = n;
        while (true) {
            if (t[k].has) res = min(res, eval(t[k], x));
            if (r - l == 1) break;
            int m = (l + r) / 2;
            if (i < m) { k = 2 * k; r = m; } else { k = 2 * k + 1; l = m; }
        }
        return res;
    }
};
// --8<-- [end:core]

int main() {
    // 乱数で愚直な方法と比べる
    mt19937 rng(2);
    for (int t = 0; t < 200; t++) {
        vector<long long> xs;
        for (int i = 0; i < 20; i++) xs.push_back((long long)(rng() % 41) - 20);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        LiChaoTree lc(xs);
        vector<pair<long long, long long>> lines;
        for (int s = 0; s < 30; s++) {
            if (rng() % 2 || lines.empty()) {
                long long a = (long long)(rng() % 21) - 10, b = (long long)(rng() % 201) - 100;
                lc.add(a, b);
                lines.push_back({a, b});
            } else {
                long long x = xs[rng() % xs.size()], best = LLONG_MAX;
                for (auto [a, b] : lines) best = min(best, a * x + b);
                assert(lc.query(x) == best);
            }
        }
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<array<long long, 3>> qs(q);
    vector<long long> xs;
    for (auto& [type, u, v] : qs) {
        cin >> type;
        if (type == 0) cin >> u >> v;
        else { cin >> u; xs.push_back(u); }
    }
    if (xs.empty()) return 0;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    LiChaoTree lc(xs);
    for (int i = 0; i < n; i++) lc.add(a[i], b[i]);
    for (auto [type, u, v] : qs) {
        if (type == 0) lc.add(u, v);
        else cout << lc.query(u) << '\n';
    }
}
