// T を S の接頭辞（空でない）の連結に分けるときの最小の個数（できなければ -1）
// 入力：S T（英小文字、空でない）
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

// --8<-- [start:core]
int min_pieces(const string& s, const string& t) {
    int m = s.size(), n = t.size();
    vector<int> v;  // S、区切り −1、T
    for (char c : s) v.push_back(c);
    v.push_back(-1);
    for (char c : t) v.push_back(c);
    vector<int> z = atcoder::z_algorithm(v);
    // len[j]：T[j] から S の接頭辞が何文字続くか。位置 j から j+1 … j+len[j] へ 1 個で進める
    vector<int> len(n);
    for (int j = 0; j < n; j++) len[j] = z[m + 1 + j];
    // 個数 c で届く範囲 [0, reach] を広げていく（BFS の段と同じ）
    int cnt = 0, reach = 0, next_reach = 0;
    for (int j = 0; j < n; j++) {
        if (j > reach) return -1;  // 位置 j にたどり着けない
        next_reach = max(next_reach, j + len[j]);
        if (j == reach) {  // 今の個数で届く最後の位置を見終えた
            if (next_reach == reach) return -1;
            cnt++;
            reach = next_reach;
        }
    }
    return cnt;
}
// --8<-- [end:core]

int naive(const string& s, const string& t) {
    int n = t.size();
    const int INF = 1 << 30;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int j = 0; j < n; j++) {
        if (dp[j] == INF) continue;
        for (int k = 1; k <= (int)s.size() && j + k <= n; k++) {
            if (t.compare(j, k, s, 0, k) != 0) break;
            dp[j + k] = min(dp[j + k], dp[j] + 1);
        }
    }
    return dp[n] == INF ? -1 : dp[n];
}

int main() {
    // a と b だけの短い文字列を全部試す
    for (int ls = 1; ls <= 3; ls++) for (int ms = 0; ms < (1 << ls); ms++)
        for (int lt = 1; lt <= 7; lt++) for (int mt = 0; mt < (1 << lt); mt++) {
            string s(ls, 'a'), t(lt, 'a');
            for (int i = 0; i < ls; i++) if (ms >> i & 1) s[i] = 'b';
            for (int i = 0; i < lt; i++) if (mt >> i & 1) t[i] = 'b';
            assert(min_pieces(s, t) == naive(s, t));
        }
    string s, t;
    cin >> s >> t;
    int ans = min_pieces(s, t);
    assert(ans == naive(s, t));
    cout << ans << '\n';
}
