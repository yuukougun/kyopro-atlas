// 文字列 S から、隣り合う位置を選ばずに 1 文字以上取り出してできる文字列の種類数（10^9 + 7 で割った余り）。
// 最も左を取る取り出し方は「前に使った位置の 2 つ先から探す」ものになる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

// --8<-- [start:core]
mint count_nonadjacent(const string& s) {
    int n = s.size();
    vector<array<int, 26>> nxt(n + 2);  // i + 2 = n + 1 も引くので番兵の行を 2 つ置く
    nxt[n].fill(n);
    nxt[n + 1].fill(n);
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
    }
    // dp[i]：最も左の取り出し方で、最後に使った位置が i の文字列の数
    vector<mint> dp(n);
    for (int c = 0; c < 26; c++)
        if (nxt[0][c] < n) dp[nxt[0][c]] += 1;  // 1 文字目
    mint ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i];
        for (int c = 0; c < 26; c++) {
            int q = nxt[i + 2][c];  // 隣の i + 1 は使えないので i + 2 から探す
            if (q < n) dp[q] += dp[i];
        }
    }
    return ans;
}
// --8<-- [end:core]

long long brute(const string& s) {
    int n = s.size();
    set<string> st;
    for (int m = 1; m < (1 << n); m++) {
        if (m & (m >> 1)) continue;  // 隣り合う位置を選んでいる
        string t;
        for (int i = 0; i < n; i++)
            if (m >> i & 1) t += s[i];
        st.insert(t);
    }
    return st.size();
}

int main() {
    mt19937 rng(2);
    for (int iter = 0; iter < 2000; iter++) {
        int n = 1 + rng() % 12;
        string s;
        for (int i = 0; i < n; i++) s += char('a' + rng() % 3);
        assert(count_nonadjacent(s).val() == brute(s));
    }
    string s;
    cin >> s;
    cout << count_nonadjacent(s).val() << '\n';
}
