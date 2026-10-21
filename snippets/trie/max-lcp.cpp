#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:trie]
// 各 i について max_{j ≠ i} LCP(s[i], s[j])（Trie の通過数で求める）
vector<int> max_lcp_trie(const vector<string>& s) {
    vector<array<int, 26>> nxt(1);
    nxt[0].fill(-1);
    vector<int> cnt(1, 0);
    for (const string& t : s) {
        int v = 0;
        for (char ch : t) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                nxt[v][c] = (int)nxt.size();
                nxt.emplace_back();
                nxt.back().fill(-1);
                cnt.push_back(0);
            }
            v = nxt[v][c];
            cnt[v]++;
        }
    }
    vector<int> res;
    for (const string& t : s) {
        // 自分の経路の上で、通過数が 2 以上（自分のほかにも通る）の最も深い節点の深さ
        int v = 0, best = 0;
        for (int d = 0; d < (int)t.size(); d++) {
            v = nxt[v][t[d] - 'a'];
            if (cnt[v] >= 2) best = d + 1;
        }
        res.push_back(best);
    }
    return res;
}
// --8<-- [end:trie]

// --8<-- [start:sort]
// 同じ値をソートで求める：辞書順で隣り合う 2 つとの LCP の大きい方
vector<int> max_lcp_sort(const vector<string>& s) {
    int n = s.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&](int a, int b) { return s[a] < s[b]; });
    auto lcp = [&](const string& a, const string& b) {
        int k = 0;
        while (k < (int)a.size() && k < (int)b.size() && a[k] == b[k]) k++;
        return k;
    };
    vector<int> res(n, 0);
    for (int k = 0; k + 1 < n; k++) {
        int l = lcp(s[idx[k]], s[idx[k + 1]]);
        res[idx[k]] = max(res[idx[k]], l);
        res[idx[k + 1]] = max(res[idx[k + 1]], l);
    }
    return res;
}
// --8<-- [end:sort]

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& t : s) cin >> t;
    vector<int> a = max_lcp_trie(s);
    assert(a == max_lcp_sort(s));
    for (int x : a) cout << x << '\n';
    return 0;
}
