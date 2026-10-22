#include <bits/stdc++.h>
using namespace std;

// X_i は閉区間 [L_i, R_i] の一様乱数（0 <= L_i < R_i、整数）で、互いに独立とする。
// K 番目に大きい値 Y の期待値を 2 通りで求め、一致を確かめる。

// --8<-- [start:core]
// E[Y] = ∫ P(Y > t) dt を、長さ 1 の区分 [x, x+1) ごとに u = t - x の多項式で積分する
double kth_max_by_integral(const vector<int>& L, const vector<int>& R, int K) {
    int n = L.size();
    int hi = *max_element(R.begin(), R.end());
    auto add = [](vector<double>& p, int d, double v) {
        if ((int)p.size() <= d) p.resize(d + 1, 0.0);
        p[d] += v;
    };
    double ans = 0;
    for (int x = 0; x < hi; x++) {
        // f[j]：t = x + u より大きい X_i がちょうど j 個である確率（u の多項式の係数）
        vector<vector<double>> f(n + 1);
        f[0] = {1.0};
        for (int i = 0; i < n; i++) {
            double a = 0, b = 0;  // P(X_i > x + u) = a + b u（0 <= u <= 1）
            if (L[i] >= x + 1) a = 1;
            else if (R[i] > x) { a = double(R[i] - x) / (R[i] - L[i]); b = -1.0 / (R[i] - L[i]); }
            vector<vector<double>> g(n + 1);
            for (int j = 0; j <= i; j++) {
                for (int d = 0; d < (int)f[j].size(); d++) {
                    double c = f[j][d];
                    add(g[j + 1], d, c * a);      // X_i が t より大きい
                    add(g[j + 1], d + 1, c * b);
                    add(g[j], d, c * (1 - a));    // X_i が t 以下
                    add(g[j], d + 1, -c * b);
                }
            }
            f = g;
        }
        // P(Y > t) = P(t より大きいものが K 個以上)。u^d の [0, 1] での積分は 1/(d+1)
        for (int j = K; j <= n; j++)
            for (int d = 0; d < (int)f[j].size(); d++) ans += f[j][d] / (d + 1);
    }
    return ans;
}
// --8<-- [end:core]

// --8<-- [start:order]
// 区分 [x, x+1) に入る個数 j と、x+1 以上の個数 k を数え、
// 区分の中の j 個の一様乱数の s 番目に大きい値の期待値 x + 1 - s/(j+1) を使う
double kth_max_by_order(const vector<int>& L, const vector<int>& R, int K) {
    int n = L.size();
    int hi = *max_element(R.begin(), R.end());
    double ans = 0;
    for (int x = 0; x < hi; x++) {
        vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0.0));
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            double w = R[i] - L[i];
            double in = (L[i] <= x && x < R[i]) ? 1 / w : 0;  // [x, x+1) に入る
            double above = L[i] >= x + 1 ? 1 : (R[i] > x + 1 ? (R[i] - x - 1) / w : 0);
            double below = 1 - in - above;
            vector<vector<double>> nd(n + 1, vector<double>(n + 1, 0.0));
            for (int j = 0; j <= i; j++) {
                for (int k = 0; j + k <= i; k++) {
                    double c = dp[j][k];
                    nd[j + 1][k] += c * in;
                    nd[j][k + 1] += c * above;
                    nd[j][k] += c * below;
                }
            }
            dp = nd;
        }
        for (int j = 0; j <= n; j++)
            for (int k = 0; j + k <= n; k++)
                if (k < K && K <= j + k) ans += dp[j][k] * (x + 1 - double(K - k) / (j + 1));
    }
    return ans;
}
// --8<-- [end:order]

int main() {
    int n, K;
    cin >> n >> K;
    vector<int> L(n), R(n);
    for (int i = 0; i < n; i++) cin >> L[i] >> R[i];
    double e1 = kth_max_by_integral(L, R, K);
    double e2 = kth_max_by_order(L, R, K);
    assert(fabs(e1 - e2) < 1e-9);
    cout << fixed << setprecision(6) << e1 << '\n';
}
