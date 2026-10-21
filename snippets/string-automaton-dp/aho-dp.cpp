// Aho-Corasick の状態の上の DP
// 入力：sigma K L、続いて K 個のパターン（'a' から sigma 種類の文字、空でない、K ≤ 20）
// 出力：長さ L の文字列のうち、どのパターンも含まないものの数と、すべてのパターンを含むものの数（mod 998244353）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:build]
struct AhoCorasick {
    int sigma;
    vector<vector<int>> nxt;  // nxt[v][c] = 状態 v で文字 c を読んだ後の状態（build の後は全部埋まる）
    vector<int> fail;         // 失敗リンク：v の文字列の真の接尾辞のうち、Trie にある最長のもの
    vector<int> out;          // v の文字列の接尾辞になっているパターンの集合（bit）

    AhoCorasick(int sigma) : sigma(sigma), nxt(1, vector<int>(sigma, -1)), fail(1, 0), out(1, 0) {}

    void add(const string& s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] < 0) {
                nxt[v][c] = nxt.size();
                nxt.push_back(vector<int>(sigma, -1));
                fail.push_back(0);
                out.push_back(0);
            }
            v = nxt[v][c];
        }
        out[v] |= 1 << id;  // 同じパターンが 2 回来ても壊れないよう、代入でなく OR
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < sigma; c++) {
            if (nxt[0][c] < 0) nxt[0][c] = 0;
            else q.push(nxt[0][c]);  // 深さ 1 の失敗リンクは根
        }
        while (!q.empty()) {  // BFS 順：fail[v] は v より浅いので、先に確定している
            int v = q.front();
            q.pop();
            out[v] |= out[fail[v]];  // 終端の印を失敗リンク先から受け継ぐ
            for (int c = 0; c < sigma; c++) {
                int u = nxt[v][c];
                if (u < 0) {
                    nxt[v][c] = nxt[fail[v]][c];  // 無い辺は失敗リンク先の遷移を写す
                } else {
                    fail[u] = nxt[fail[v]][c];
                    q.push(u);
                }
            }
        }
    }

    int size() const { return nxt.size(); }
};
// --8<-- [end:build]

mint count_avoid(const AhoCorasick& ac, int len) {
    // --8<-- [start:avoid]
    int s = ac.size();
    vector<mint> dp(s, 0);  // dp[v] = 状態が v で、まだどのパターンも含まない文字列の数
    dp[0] = 1;
    for (int step = 0; step < len; step++) {
        vector<mint> ndp(s, 0);
        for (int v = 0; v < s; v++) {
            if (dp[v] == 0) continue;
            for (int c = 0; c < ac.sigma; c++) {
                int u = ac.nxt[v][c];
                if (ac.out[u] == 0) ndp[u] += dp[v];  // パターンで終わる状態には入れない
            }
        }
        dp = ndp;
    }
    mint ans = 0;
    for (int v = 0; v < s; v++) ans += dp[v];
    // --8<-- [end:avoid]
    return ans;
}

mint count_all(const AhoCorasick& ac, int k, int len) {
    // --8<-- [start:all]
    int s = ac.size(), full = (1 << k) - 1;
    // dp[mask][v] = 状態が v で、含んだパターンの集合が mask の文字列の数
    vector<vector<mint>> dp(1 << k, vector<mint>(s, 0));
    dp[0][0] = 1;
    for (int step = 0; step < len; step++) {
        vector<vector<mint>> ndp(1 << k, vector<mint>(s, 0));
        for (int mask = 0; mask <= full; mask++) {
            for (int v = 0; v < s; v++) {
                if (dp[mask][v] == 0) continue;
                for (int c = 0; c < ac.sigma; c++) {
                    int u = ac.nxt[v][c];
                    ndp[mask | ac.out[u]][u] += dp[mask][v];  // u で終わるパターンを集合に足す
                }
            }
        }
        dp = ndp;
    }
    mint ans = 0;
    for (int v = 0; v < s; v++) ans += dp[full][v];
    // --8<-- [end:all]
    return ans;
}

// 素朴な数え上げ（確かめ用）
pair<long long, long long> brute(int sigma, const vector<string>& ps, int len) {
    long long total = 1;
    for (int i = 0; i < len; i++) total *= sigma;
    long long avoid = 0, all = 0;
    for (long long x = 0; x < total; x++) {
        string t(len, 'a');
        long long y = x;
        for (int i = 0; i < len; i++) {
            t[i] = 'a' + y % sigma;
            y /= sigma;
        }
        int cnt = 0;
        for (const string& p : ps) cnt += (t.find(p) != string::npos);
        if (cnt == 0) avoid++;
        if (cnt == (int)ps.size()) all++;
    }
    return {avoid % 998244353, all % 998244353};
}

int main() {
    // 小さい場合を素朴な数え上げと比べる
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int sigma = 2 + rng() % 2, k = 1 + rng() % 3, len = rng() % 9;
        vector<string> ps(k);
        AhoCorasick ac(sigma);
        for (int i = 0; i < k; i++) {
            int m = 1 + rng() % 4;
            for (int j = 0; j < m; j++) ps[i] += 'a' + rng() % sigma;
            ac.add(ps[i], i);
        }
        ac.build();
        auto [a, b] = brute(sigma, ps, len);
        assert(count_avoid(ac, len).val() == a);
        assert(count_all(ac, k, len).val() == b);
    }

    int sigma, k, len;
    cin >> sigma >> k >> len;
    AhoCorasick ac(sigma);
    for (int i = 0; i < k; i++) {
        string p;
        cin >> p;
        ac.add(p, i);
    }
    ac.build();
    cout << count_avoid(ac, len).val() << ' ' << count_all(ac, k, len).val() << '\n';
}
