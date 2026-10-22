#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// f(x) = min_f + Σ_{l∈L} max(0, l − x) + Σ_{r∈R} max(0, x − r)、max L ≤ min R を保つ
struct SlopeTrick {
    long long min_f = 0;
    priority_queue<long long> L;                                // 最大が先頭
    priority_queue<long long, vector<long long>, greater<>> R;  // 最小が先頭
    long long add_l = 0, add_r = 0;  // L・R の全要素に足す値（遅延）
    static constexpr long long INF = numeric_limits<long long>::max() / 4;

    // 空なら ±∞（∞ に add_l・add_r を足さない）
    long long top_l() const { return L.empty() ? -INF : L.top() + add_l; }
    long long top_r() const { return R.empty() ? INF : R.top() + add_r; }
    void push_l(long long a) { L.push(a - add_l); }
    void push_r(long long a) { R.push(a - add_r); }
    long long pop_l() { long long v = top_l(); L.pop(); return v; }
    long long pop_r() { long long v = top_r(); R.pop(); return v; }

    void add_const(long long c) { min_f += c; }
    // max(0, x − a) を足す：l0 は最小点のまま残る
    void add_x_minus_a(long long a) {
        if (!L.empty()) min_f += max(0LL, top_l() - a);
        push_l(a);
        push_r(pop_l());
    }
    // max(0, a − x) を足す
    void add_a_minus_x(long long a) {
        if (!R.empty()) min_f += max(0LL, a - top_r());
        push_r(a);
        push_l(pop_r());
    }
    void add_abs(long long a) { add_x_minus_a(a); add_a_minus_x(a); }
    void clear_right() { R = {}; }  // f(x) ← min_{y ≤ x} f(y)
    void clear_left() { L = {}; }   // f(x) ← min_{y ≥ x} f(y)
    // f(x) ← min_{x − b ≤ y ≤ x − a} f(y)（a ≤ b）。L は a、R は b だけ右へ
    void slide_min(long long a, long long b) { add_l += a; add_r += b; }
    void translate(long long a) { slide_min(a, a); }  // f(x) ← f(x − a)
};
// --8<-- [end:core]

// f(x) を求める（確かめ用。ヒープを写して O(N log N)）
long long eval(SlopeTrick st, long long x) {
    long long v = st.min_f;
    while (!st.L.empty()) v += max(0LL, st.pop_l() - x);
    while (!st.R.empty()) v += max(0LL, x - st.pop_r());
    return v;
}

// 乱数の操作の列を、範囲 [−W, W] の配列で持った関数と比べる
void stress() {
    mt19937 rng(12345);
    const int W = 300, C = 40;  // 傾きの変わる点は [−C, C] の付近に収める
    auto rnd = [&](int lo, int hi) { return (int)(rng() % (hi - lo + 1)) + lo; };
    for (int iter = 0; iter < 300; iter++) {
        SlopeTrick st;
        vector<long long> f(2 * W + 1, 0);  // f[x + W]
        for (int step = 0; step < 30; step++) {
            int type = rnd(0, 6);
            long long a = rnd(-C / 2, C / 2);
            vector<long long> g = f;
            if (type == 0) {
                st.add_abs(a);
                for (int x = -W; x <= W; x++) g[x + W] += llabs(x - a);
            } else if (type == 1) {
                st.add_x_minus_a(a);
                for (int x = -W; x <= W; x++) g[x + W] += max(0LL, x - a);
            } else if (type == 2) {
                st.add_a_minus_x(a);
                for (int x = -W; x <= W; x++) g[x + W] += max(0LL, a - x);
            } else if (type == 3) {
                st.add_const(a);
                for (auto& v : g) v += a;
            } else if (type == 4) {
                st.clear_right();
                for (int i = 1; i <= 2 * W; i++) g[i] = min(g[i], g[i - 1]);
            } else if (type == 5) {
                st.clear_left();
                for (int i = 2 * W - 1; i >= 0; i--) g[i] = min(g[i], g[i + 1]);
            } else {
                long long lo = rnd(-2, 2), hi = lo + rnd(0, 2);
                st.slide_min(lo, hi);
                for (int x = -W; x <= W; x++) {
                    // 範囲の外は端の値で代える（端の外では f は単調で、端より小さくならない）
                    long long best = LLONG_MAX;
                    for (long long y = x - hi; y <= x - lo; y++)
                        best = min(best, f[clamp<long long>(y, -W, W) + W]);
                    g[x + W] = best;
                }
            }
            f = g;
            long long mn = *min_element(f.begin(), f.end());
            assert(st.min_f == mn);
            for (int x = -C; x <= C; x++) assert(eval(st, x) == f[x + W]);
            if (!st.L.empty() && !st.R.empty()) assert(st.top_l() <= st.top_r());
        }
    }
}

int main() {
    stress();
    // 数列 A を広義単調増加の列 B に変えるときの Σ|A_i − B_i| の最小
    int n;
    cin >> n;
    SlopeTrick st;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        st.clear_right();  // dp[i−1] の累積 min を取る
        st.add_abs(a);     // |x − A_i| を足す
    }
    cout << st.min_f << '\n';
}
