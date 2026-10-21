// 任意の 2 接尾辞の LCP を、LCP 配列の区間最小（Sparse Table）で O(1) で答える
// 入力：S、Q、続く Q 行に位置 i j。出力：LCP(S[i..), S[j..))
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    // --8<-- [start:core]
    vector<int> sa = atcoder::suffix_array(s);
    vector<int> lcp = atcoder::lcp_array(s, sa);
    vector<int> rnk(n);
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;

    // Sparse Table：st[k][i] = min(lcp[i], …, lcp[i + 2^k - 1])
    int m = lcp.size();
    vector<vector<int>> st(1, lcp);
    for (int k = 1; (1 << k) <= m; k++) {
        st.emplace_back(m - (1 << k) + 1);
        for (int i = 0; i + (1 << k) <= m; i++)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
    auto lcp_of = [&](int i, int j) -> int {  // LCP(s[i..), s[j..))
        if (i == j) return n - i;             // 同じ接尾辞なら長さそのもの
        int l = rnk[i], r = rnk[j];
        if (l > r) swap(l, r);                // 区間は lcp[l], …, lcp[r - 1]
        int k = __lg(r - l);
        return min(st[k][l], st[k][r - (1 << k)]);
    };
    // --8<-- [end:core]

    for (int t = 0; t < q; t++) {
        int i, j;
        cin >> i >> j;
        int naive = 0;
        while (i + naive < n && j + naive < n && s[i + naive] == s[j + naive]) naive++;
        assert(lcp_of(i, j) == naive);
        cout << lcp_of(i, j) << '\n';
    }
}
