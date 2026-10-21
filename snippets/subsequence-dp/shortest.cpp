// 文字列 S の部分列として現れない最短の文字列のうち、辞書順最小のもの（文字は先頭の sigma 種類）。
// 後ろから最短の長さを DP し、先頭から「最短を保つ最小の文字」を選んで復元する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
string shortest_non_subsequence(const string& s, int sigma) {
    int n = s.size();
    vector<array<int, 26>> nxt(n + 1);
    nxt[n].fill(n);
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
    }
    // len[i]：S[i, n) の部分列にならない最短の長さ。len[n + 1] = 0 は「c を拾えなかった」を表す
    vector<int> len(n + 2, 0);
    for (int i = n; i >= 0; i--) {
        len[i] = INT_MAX;
        for (int c = 0; c < sigma; c++) len[i] = min(len[i], 1 + len[nxt[i][c] + 1]);
    }
    string ans;
    int p = 0;
    while (p != n + 1) {  // 拾えない文字を置いたら終わり
        for (int c = 0; c < sigma; c++) {
            if (len[nxt[p][c] + 1] == len[p] - 1) {  // 最短を保つ最小の文字
                ans += char('a' + c);
                p = nxt[p][c] + 1;
                break;
            }
        }
    }
    return ans;
}
// --8<-- [end:core]

bool is_subsequence(const string& t, const string& s) {
    size_t j = 0;
    for (char ch : s)
        if (j < t.size() && t[j] == ch) j++;
    return j == t.size();
}

// 全列挙：長さの短い順、同じ長さでは辞書順に試す
string brute(const string& s, int sigma) {
    for (int len = 1;; len++) {
        int total = 1;
        for (int i = 0; i < len; i++) total *= sigma;
        for (int m = 0; m < total; m++) {
            string t(len, 'a');
            for (int i = len - 1, x = m; i >= 0; i--, x /= sigma) t[i] = char('a' + x % sigma);
            if (!is_subsequence(t, s)) return t;
        }
    }
}

int main() {
    mt19937 rng(3);
    for (int iter = 0; iter < 2000; iter++) {
        int sigma = 2 + rng() % 2;
        int n = rng() % 11;
        string s;
        for (int i = 0; i < n; i++) s += char('a' + rng() % sigma);
        assert(shortest_non_subsequence(s, sigma) == brute(s, sigma));
    }
    string s;
    int sigma;
    cin >> s >> sigma;
    if (s == "-") s = "";
    cout << shortest_non_subsequence(s, sigma) << '\n';
}
