#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<int> wt(n);
    vector<long long> val(n);
    for (int i = 0; i < n; i++) cin >> wt[i] >> val[i];

    // --8<-- [start:core]
    // pre[i][j]：品物 0..i-1 から重さの和 j 以下で選んだときの価値の最大
    // suf[i][j]：品物 i..n-1 から重さの和 j 以下で選んだときの価値の最大
    vector<vector<long long>> pre(n + 1, vector<long long>(w + 1, 0));
    vector<vector<long long>> suf(n + 1, vector<long long>(w + 1, 0));
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i];
        for (int j = wt[i]; j <= w; j++) pre[i + 1][j] = max(pre[i + 1][j], pre[i][j - wt[i]] + val[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        for (int j = wt[i]; j <= w; j++) suf[i][j] = max(suf[i][j], suf[i + 1][j - wt[i]] + val[i]);
    }
    // 品物 i を除いた最大：前の i 個に j、後ろに w - j を割り振る
    vector<long long> without(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= w; j++) without[i] = max(without[i], pre[i][j] + suf[i + 1][w - j]);
    }
    // --8<-- [end:core]

    // 全探索で確かめる（n が小さいときだけ）
    if (n <= 12) {
        for (int i = 0; i < n; i++) {
            long long best = 0;
            for (int m = 0; m < (1 << n); m++) {
                if (m >> i & 1) continue;
                long long sw = 0, sv = 0;
                for (int t = 0; t < n; t++)
                    if (m >> t & 1) sw += wt[t], sv += val[t];
                if (sw <= w) best = max(best, sv);
            }
            assert(best == without[i]);
        }
    }
    for (int i = 0; i < n; i++) cout << without[i] << (i + 1 < n ? ' ' : '\n');
    if (n == 0) cout << '\n';
}
