#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:mex]
// 列 a の mex。長さ n の列の mex は n 以下なので、n より大きい値は無視する
int mex_of(const vector<int>& a) {
    int n = a.size();
    vector<bool> seen(n + 1, false);  // 答えが n になりうるので n + 1 個
    for (int x : a) {
        if (0 <= x && x <= n) seen[x] = true;
    }
    int m = 0;
    while (seen[m]) m++;  // seen[n] まで true になることはない
    return m;
}
// --8<-- [end:mex]

// --8<-- [start:gaps]
// 長さ m の窓すべての mex の最小値。
// 値 k を含まない長さ m の窓がある ⇔ k の出現位置の間（両端の番兵 -1 と n を含む）に長さ m 以上の隙間がある
int window_mex_min(const vector<int>& a, int m) {
    int n = a.size();
    vector<int> last(n + 1, -1);   // 値 k の直前の出現位置（番兵 -1）
    vector<int> gap(n + 1, 0);     // 値 k を含まない連続部分の最大の長さ
    for (int i = 0; i < n; i++) {
        int k = a[i];
        if (k > n) continue;       // n より大きい値は答えに関係しない
        gap[k] = max(gap[k], i - last[k] - 1);
        last[k] = i;
    }
    for (int k = 0; k <= n; k++) {
        gap[k] = max(gap[k], n - last[k] - 1);  // 末尾の番兵 n までの隙間
        if (gap[k] >= m) return k;
    }
    return -1;  // m <= n なら k = n で必ず見つかる（ここには来ない）
}
// --8<-- [end:gaps]

int naive(const vector<int>& a, int m) {
    int n = a.size(), best = INT_MAX;
    for (int l = 0; l + m <= n; l++) {
        best = min(best, mex_of(vector<int>(a.begin() + l, a.begin() + l + m)));
    }
    return best;
}

int main() {
    // 小さい列で素朴な方法と照合する
    mt19937 rng(1);
    for (int t = 0; t < 2000; t++) {
        int n = rng() % 8 + 1, m = rng() % n + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % (n + 2);
        assert(window_mex_min(a, m) == naive(a, m));
    }
    assert(mex_of({}) == 0);
    assert(mex_of({1, 2}) == 0);
    assert(mex_of({0, 1, 3}) == 2);
    assert(mex_of({0, 1, 2}) == 3);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << window_mex_min(a, m) << '\n';
}
