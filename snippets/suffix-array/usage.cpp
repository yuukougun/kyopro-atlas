// ACL の suffix_array・lcp_array と、異なる部分文字列の数
// 入力：文字列 S（1 文字以上）。出力：sa、lcp、異なる部分文字列の数
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // --8<-- [start:core]
    vector<int> sa = atcoder::suffix_array(s);       // sa[i]：辞書順で i 番目の接尾辞の開始位置
    vector<int> lcp = atcoder::lcp_array(s, sa);     // 長さ n - 1。lcp[i] = LCP(s[sa[i]..), s[sa[i+1]..))
    vector<int> rnk(n);                              // sa の逆写像：位置 p の接尾辞は辞書順で rnk[p] 番目
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;

    long long distinct = (long long)n * (n + 1) / 2;  // 重複込みの部分文字列の数
    for (int x : lcp) distinct -= x;                  // 直前の接尾辞と共通の接頭辞は数え済み
    // --8<-- [end:core]

    // 素朴な方法で確かめる
    vector<int> naive(n);
    iota(naive.begin(), naive.end(), 0);
    sort(naive.begin(), naive.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    assert(sa == naive);
    for (int p = 0; p < n; p++) assert(sa[rnk[p]] == p);
    set<string> subs;
    for (int l = 0; l < n; l++)
        for (int r = l + 1; r <= n; r++) subs.insert(s.substr(l, r - l));
    assert((long long)subs.size() == distinct);

    for (int i = 0; i < n; i++) cout << sa[i] << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i + 1 < n; i++) cout << lcp[i] << (i + 2 < n ? ' ' : '\n');
    if (n == 1) cout << '\n';
    cout << distinct << '\n';
}
