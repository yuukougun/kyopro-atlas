// 自作の Suffix Array（ダブリング O(N log^2 N)）と LCP 配列（Kasai 法 O(N)）
// 入力：文字列 S（1 文字以上）。出力：sa と lcp
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

// --8<-- [start:core]
vector<int> build_sa(const string& s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) sa[i] = i, rnk[i] = (unsigned char)s[i];
    for (int w = 1;; w *= 2) {
        // 先頭 2w 文字の順位は (先頭 w 文字の順位, 続く w 文字の順位) の組で決まる。はみ出しは -1
        auto key = [&](int i) { return pair(rnk[i], i + w < n ? rnk[i + w] : -1); };
        sort(sa.begin(), sa.end(), [&](int a, int b) { return key(a) < key(b); });
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (key(sa[i - 1]) < key(sa[i]));
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1 || w >= n) break;  // 順位がすべて異なれば確定
    }
    return sa;
}

vector<int> build_lcp(const string& s, const vector<int>& sa) {  // Kasai 法
    int n = s.size();
    vector<int> rnk(n), lcp(max(n - 1, 0));
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;
    int h = 0;
    for (int p = 0; p < n; p++) {   // 位置の順に回す
        if (h > 0) h--;             // 位置 p - 1 の値から 1 しか減らない
        if (rnk[p] == 0) { h = 0; continue; }
        int q = sa[rnk[p] - 1];     // 辞書順で直前の接尾辞
        while (p + h < n && q + h < n && s[p + h] == s[q + h]) h++;
        lcp[rnk[p] - 1] = h;
    }
    return lcp;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    vector<int> sa = build_sa(s), lcp = build_lcp(s, sa);
    assert(sa == atcoder::suffix_array(s));
    assert(lcp == atcoder::lcp_array(s, sa));
    int n = s.size();
    for (int i = 0; i < n; i++) cout << sa[i] << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i + 1 < n; i++) cout << lcp[i] << (i + 2 < n ? ' ' : '\n');
    if (n == 1) cout << '\n';
}
