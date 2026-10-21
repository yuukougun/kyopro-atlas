// 回転どうしの比較：S の回転と T の回転の組 (i, j) で、S の回転 ≤ T の回転となるものを数える（|S| = |T| = N）
// 入力：N、S、T。出力：組の数
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    int n;
    string s, t;
    cin >> n >> s >> t;
    // --8<-- [start:core]
    string x = s + s + t + t;  // 位置 i < n の接尾辞の先頭 n 文字が S の回転、位置 2n + j なら T の回転
    vector<int> sa = atcoder::suffix_array(x);
    vector<int> lcp = atcoder::lcp_array(x, sa);
    long long ans = 0, s_seen = 0;  // s_seen：今のブロックまでに出た S の回転の数
    int m = x.size();
    for (int i = 0; i < m;) {
        // 先頭 n 文字が等しい接尾辞（lcp >= n でつながる範囲）を 1 つのブロックにまとめる
        int j = i + 1;
        while (j < m && lcp[j - 1] >= n) j++;
        long long cs = 0, ct = 0;
        for (int k = i; k < j; k++) {
            if (sa[k] < n) cs++;
            else if (2 * n <= sa[k] && sa[k] < 3 * n) ct++;
        }
        s_seen += cs;          // 同じブロックの S の回転は「等しい」ので ≤ に入る
        ans += ct * s_seen;
        i = j;
    }
    // --8<-- [end:core]

    long long naive = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (s.substr(i) + s.substr(0, i) <= t.substr(j) + t.substr(0, j)) naive++;
    assert(ans == naive);
    cout << ans << '\n';
}
