#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 全ペア (i < j) の LCP の長さの和
long long lcp_sum(const vector<string>& s) {
    vector<array<int, 26>> nxt(1);
    nxt[0].fill(-1);
    vector<long long> cnt(1, 0);  // 通過数
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
    long long ans = 0;
    for (int v = 1; v < (int)cnt.size(); v++) {  // 根（深さ 0）は数えない
        ans += cnt[v] * (cnt[v] - 1) / 2;         // そこを通る組の数 C(cnt, 2)
    }
    return ans;
}
// --8<-- [end:core]

long long brute(const vector<string>& s) {
    long long ans = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = 0;
            while (k < (int)s[i].size() && k < (int)s[j].size() && s[i][k] == s[j][k]) k++;
            ans += k;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& t : s) cin >> t;
    long long ans = lcp_sum(s);
    assert(ans == brute(s));
    cout << ans << '\n';
    return 0;
}
