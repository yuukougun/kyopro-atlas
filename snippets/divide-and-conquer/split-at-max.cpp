// 最大値の位置で区間を割る分割統治（例：隣の真に小さい要素を吸収し続けたときの最終的な大きさ）
// 入力：N、A_0 … A_{N-1}。出力：各 k から始めたときの最終的な大きさ
// 区間の最大値の位置（同じ値なら最も左）を Sparse Table で引き、再帰の代わりに明示的なスタックで回す
// 小さい乱数の列で素朴なシミュレーションと比べて assert する
#include <bits/stdc++.h>
using namespace std;

// 最大値の位置の Sparse Table（同じ値なら左を返す）
struct ArgMax {
    const vector<long long>& a;
    vector<vector<int>> sp;
    int better(int i, int j) const { return a[j] > a[i] ? j : i; }  // i < j で呼ぶ
    ArgMax(const vector<long long>& a_) : a(a_), sp(1, vector<int>(a_.size())) {
        int n = a.size();
        for (int i = 0; i < n; i++) sp[0][i] = i;
        for (int k = 1; (1 << k) <= n; k++) {
            sp.emplace_back(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= n; i++) {
                sp[k][i] = better(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    int operator()(int l, int r) const {  // [l, r) の最大値の位置（l < r）
        int k = bit_width(unsigned(r - l)) - 1;
        return better(sp[k][l], sp[k][r - (1 << k)]);
    }
};

// --8<-- [start:core]
vector<long long> solve(const vector<long long>& a) {
    int n = a.size();
    vector<long long> s(n + 1, 0);  // 累積和：[l, r) の和は s[r] - s[l]
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
    ArgMax argmax(a);  // argmax(l, r)：[l, r) の最大値の位置（同じ値なら最も左）

    vector<long long> ans(n);
    // (l, r, 親の値, 親の g)。g は「その区間をすべて吸収した状態から最後にどこまで育つか」
    struct Item { int l, r; long long pv, pg; };
    vector<Item> st;
    if (n > 0) st.push_back({0, n, -1, -1});  // 根には親がない（pv = -1）
    while (!st.empty()) {
        auto [l, r, pv, pg] = st.back();
        st.pop_back();
        int m = argmax(l, r);
        long long sum = s[r] - s[l];
        long long g = (pv == -1 || sum <= pv) ? sum : pg;  // 親を吸収できれば親の g と同じ
        // m の左は m より真に小さい。区間が 1 つだけか、隣に真に小さい要素があれば区間を吸収しきる
        bool full = (r - l == 1) || (m > l) || (a[m + 1] < a[m]);
        ans[m] = full ? g : a[m];  // 吸収できないなら外の境界も a[m] 以上なので動けない
        if (l < m) st.push_back({l, m, a[m], g});
        if (m + 1 < r) st.push_back({m + 1, r, a[m], g});
    }
    return ans;
}
// --8<-- [end:core]

vector<long long> naive(const vector<long long>& a) {
    int n = a.size();
    vector<long long> ans(n);
    for (int k = 0; k < n; k++) {
        int l = k, r = k + 1;
        long long cur = a[k];
        while (true) {
            if (l > 0 && a[l - 1] < cur) cur += a[--l];
            else if (r < n && a[r] < cur) cur += a[r++];
            else break;
        }
        ans[k] = cur;
    }
    return ans;
}

int main() {
    mt19937 rng(12345);
    for (int t = 0; t < 3000; t++) {
        int n = rng() % 9 + 1;
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 5 + 1;
        assert(solve(a) == naive(a));
    }
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> ans = solve(a);
    assert(ans == naive(a));
    for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 < n ? ' ' : '\n');
}
