// 各位置 p について、全接尾辞との LCP の和 Σ_q LCP(S[p..), S[q..)) を単調スタックで O(N) で求める
// 入力：S。出力：位置 0, 1, …, N-1 の答え
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> sa = atcoder::suffix_array(s);
    vector<int> lcp = atcoder::lcp_array(s, sa);
    // --8<-- [start:core]
    // left[k] = Σ_{i<k} min(lcp[i], …, lcp[k-1])：順位 k より前の接尾辞との LCP の和
    vector<long long> left(n, 0), right(n, 0);
    vector<int> stk;  // lcp の添字。lcp の値が真に増える順に積む
    for (int k = 1; k < n; k++) {
        int h = lcp[k - 1];
        while (!stk.empty() && lcp[stk.back()] >= h) stk.pop_back();
        if (stk.empty()) left[k] = (long long)h * k;  // 前の k 個すべてとの LCP が h
        else {
            int j = stk.back();                          // lcp[j] < h となる最後の添字
            left[k] = left[j + 1] + (long long)h * (k - 1 - j);
        }
        stk.push_back(k - 1);
    }
    stk.clear();
    // right[k] = Σ_{i>k} min(lcp[k], …, lcp[i-1])：左右を入れ替えて同じことをする
    for (int k = n - 2; k >= 0; k--) {
        int h = lcp[k];
        while (!stk.empty() && lcp[stk.back()] >= h) stk.pop_back();
        if (stk.empty()) right[k] = (long long)h * (n - 1 - k);
        else {
            int j = stk.back();                          // lcp[j] < h となる最初の添字
            right[k] = right[j] + (long long)h * (j - k);
        }
        stk.push_back(k);
    }
    vector<long long> ans(n);
    for (int k = 0; k < n; k++) ans[sa[k]] = left[k] + right[k] + (n - sa[k]);  // 自分自身との LCP は長さ
    // --8<-- [end:core]

    for (int p = 0; p < n; p++) {
        long long naive = 0;
        for (int q = 0; q < n; q++) {
            int l = 0;
            while (p + l < n && q + l < n && s[p + l] == s[q + l]) l++;
            naive += l;
        }
        assert(ans[p] == naive);
    }
    for (int p = 0; p < n; p++) cout << ans[p] << '\n';
}
