// 複数の文字列を区切りを挟んで 1 本の vector<int> に連結し、どれかの文字列に現れる異なる部分文字列の数を求める
// 入力：K、続く K 個の文字列（英小文字）。出力：異なる部分文字列の数
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    int k;
    cin >> k;
    vector<string> strs(k);
    for (auto& t : strs) cin >> t;
    // --8<-- [start:core]
    // 文字は 1〜26、区切りは 27, 28, … と、文字とも互いとも違う値にする
    vector<int> v;
    for (int j = 0; j < k; j++) {
        for (char c : strs[j]) v.push_back(c - 'a' + 1);
        v.push_back(27 + j);
    }
    int n = v.size();
    vector<int> sa = atcoder::suffix_array(v, 26 + k);  // 値の上限を渡すと O(n + upper)
    vector<int> lcp = atcoder::lcp_array(v, sa);
    // len[p]：位置 p から次の区切りの手前までの長さ（区切りの位置では 0）
    vector<int> len(n);
    for (int p = n - 1; p >= 0; p--)
        len[p] = (v[p] > 26) ? 0 : len[p + 1] + 1;  // 末尾は必ず区切りなので p + 1 < n
    long long distinct = 0;
    for (int i = 0; i < n; i++)
        distinct += len[sa[i]] - (i > 0 ? lcp[i - 1] : 0);
    // --8<-- [end:core]

    set<string> subs;
    for (auto& t : strs)
        for (int l = 0; l < (int)t.size(); l++)
            for (int r = l + 1; r <= (int)t.size(); r++) subs.insert(t.substr(l, r - l));
    assert((long long)subs.size() == distinct);
    cout << distinct << '\n';
}
