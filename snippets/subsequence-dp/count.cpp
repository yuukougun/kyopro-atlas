// 文字列 S の異なる部分列（空文字列を含む）の個数を 998244353 で割った余りで求める。
// 最も左を取る取り出し方だけを、次の出現位置の表で配る DP で数える。
// 値の種類が多い列には、直前の出現位置で貰う形（count_by_prev）を使う。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint count_distinct(const string& s) {
    int n = s.size();
    vector<array<int, 26>> nxt(n + 1);
    nxt[n].fill(n);  // 番兵の行
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
    }
    // dp[p]：最も左の取り出し方で、最後に使った位置が p - 1 の部分列の数（dp[0] は空文字列）
    vector<mint> dp(n + 1);
    dp[0] = 1;
    for (int p = 0; p < n; p++) {  // 配る先は p より右なので、左から確定する
        for (int c = 0; c < 26; c++) {
            int q = nxt[p][c];  // 次の文字 c は、まだ使っていない最も左の q で取る
            if (q < n) dp[q + 1] += dp[p];
        }
    }
    mint ans = 0;
    for (int p = 0; p <= n; p++) ans += dp[p];
    return ans;  // 空文字列を含む。含めないなら 1 を引く
}
// --8<-- [end:core]

// --8<-- [start:prev]
// f[i]：a[0, i) の異なる部分列（空を含む）の数。f[i + 1] = 2 f[i] - f[l]（l は a[i] の直前の出現位置）
mint count_by_prev(const vector<long long>& a) {
    int n = a.size();
    vector<mint> f(n + 1);
    f[0] = 1;
    map<long long, int> last;  // 値 → 直前に現れた位置
    for (int i = 0; i < n; i++) {
        f[i + 1] = f[i] * 2;  // a[i] を使わないもの＋末尾に a[i] を付けたもの
        auto it = last.find(a[i]);
        if (it != last.end()) f[i + 1] -= f[it->second];  // a[0, l) の部分列＋a[i] は前から数えてある
        last[a[i]] = i;
    }
    return f[n];
}
// --8<-- [end:prev]

// 全列挙：部分列をすべて作って集合に入れる
long long brute(const string& s) {
    int n = s.size();
    set<string> st;
    for (int m = 0; m < (1 << n); m++) {
        string t;
        for (int i = 0; i < n; i++)
            if (m >> i & 1) t += s[i];
        st.insert(t);
    }
    return st.size();
}

int main() {
    // 小さい場合に全列挙と比べる（文字は a〜c、長さ 0〜10）
    mt19937 rng(1);
    for (int iter = 0; iter < 2000; iter++) {
        int n = rng() % 11;
        string s;
        vector<long long> a;
        for (int i = 0; i < n; i++) {
            s += char('a' + rng() % 3);
            a.push_back(s.back() - 'a');
        }
        long long b = brute(s);
        assert(count_distinct(s).val() == b);
        assert(count_by_prev(a).val() == b);
    }
    string s;
    cin >> s;
    if (s == "-") s = "";  // 空文字列の入力
    cout << count_distinct(s).val() << '\n';
}
