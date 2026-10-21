// 文字列 S の空でない異なる部分列のうち、辞書順で K 番目のもの（なければ -1）。
// 後ろから「S[i, n) の異なる部分列の数」を数え、K + 1 で頭打ちにして先頭から決める。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
string kth_subsequence(const string& s, long long k) {
    int n = s.size();
    vector<array<int, 26>> nxt(n + 1);
    nxt[n].fill(n);
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
    }
    const long long cap = k + 1;  // 比べたいのは「k + 1 以上か」まで
    // cnt[i]：S[i, n) の異なる部分列（空を含む）の数を cap で頭打ちにしたもの
    vector<long long> cnt(n + 1);
    cnt[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        cnt[i] = 1;  // 空文字列
        for (int c = 0; c < 26; c++)
            if (nxt[i][c] < n) cnt[i] = min(cap, cnt[i] + cnt[nxt[i][c] + 1]);
    }
    if (cnt[0] - 1 < k) return "-1";  // 空でないものが k 個もない
    string ans;
    int p = 0;
    while (true) {
        for (int c = 0; c < 26; c++) {
            int q = nxt[p][c];
            if (q == n) continue;
            long long num = cnt[q + 1];  // いまの答え＋c で始まるものの数
            if (k <= num) {
                ans += char('a' + c);
                p = q + 1;
                break;
            }
            k -= num;  // c で始まるものはすべて答えより前にある
        }
        if (--k == 0) return ans;  // いまの答えそのものが、この接頭辞で始まるものの最初
    }
}
// --8<-- [end:core]

int main() {
    mt19937 rng(4);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 11;
        string s;
        for (int i = 0; i < n; i++) s += char('a' + rng() % 3);
        set<string> st;
        for (int m = 1; m < (1 << n); m++) {
            string t;
            for (int i = 0; i < n; i++)
                if (m >> i & 1) t += s[i];
            st.insert(t);
        }
        long long k = 1;
        for (auto& t : st) assert(kth_subsequence(s, k++) == t);
        assert(kth_subsequence(s, k) == "-1");
    }
    string s;
    long long k;
    cin >> s >> k;
    cout << kth_subsequence(s, k) << '\n';
}
