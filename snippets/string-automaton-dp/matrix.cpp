// 長さ N（≤ 10^18）の文字列のうち、どのパターンも含まないものの数：遷移行列の累乗
// 入力：sigma K N、続いて K 個のパターン（'a' から sigma 種類の文字、空でない）
// 出力：個数（mod 998244353）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;
using Matrix = vector<vector<mint>>;

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

Matrix mul(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix c(n, vector<mint>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            if (a[i][k] == 0) continue;
            for (int j = 0; j < n; j++) c[i][j] += a[i][k] * b[k][j];
        }
    return c;
}

vector<mint> apply(const Matrix& a, const vector<mint>& x) {
    int n = a.size();
    vector<mint> y(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) y[i] += a[i][j] * x[j];
    return y;
}

mint count_avoid_pow(const AhoCorasick& ac, long long len) {
    // --8<-- [start:matrix]
    int s = ac.size();
    // a[u][v] = 状態 v から 1 文字で状態 u に移る文字の数（パターンで終わる状態は行も列も 0）
    Matrix a(s, vector<mint>(s, 0));
    for (int v = 0; v < s; v++) {
        if (ac.out[v] != 0) continue;
        for (int c = 0; c < ac.sigma; c++) {
            int u = ac.nxt[v][c];
            if (ac.out[u] == 0) a[u][v] += 1;
        }
    }
    vector<mint> x(s, 0);  // x = A^len e_0（根から始める）
    x[0] = 1;
    for (long long e = len; e > 0; e >>= 1) {  // A の累乗どうしは掛ける順を入れ替えてよい
        if (e & 1) x = apply(a, x);
        a = mul(a, a);
    }
    mint ans = 0;
    for (int v = 0; v < s; v++) ans += x[v];
    // --8<-- [end:matrix]
    return ans;
}

mint count_avoid_dp(const AhoCorasick& ac, int len) {
    int s = ac.size();
    vector<mint> dp(s, 0);
    dp[0] = 1;
    for (int step = 0; step < len; step++) {
        vector<mint> ndp(s, 0);
        for (int v = 0; v < s; v++)
            for (int c = 0; c < ac.sigma; c++) {
                int u = ac.nxt[v][c];
                if (ac.out[u] == 0) ndp[u] += dp[v];
            }
        dp = ndp;
    }
    mint ans = 0;
    for (int v = 0; v < s; v++) ans += dp[v];
    return ans;
}

int main() {
    mt19937 rng(777);
    for (int iter = 0; iter < 200; iter++) {
        int sigma = 2 + rng() % 3, k = 1 + rng() % 3, len = rng() % 40;
        AhoCorasick ac(sigma);
        for (int i = 0; i < k; i++) {
            string p;
            int m = 1 + rng() % 5;
            for (int j = 0; j < m; j++) p += 'a' + rng() % sigma;
            ac.add(p, i);
        }
        ac.build();
        assert(count_avoid_pow(ac, len) == count_avoid_dp(ac, len));
    }

    int sigma, k;
    long long len;
    cin >> sigma >> k >> len;
    AhoCorasick ac(sigma);
    for (int i = 0; i < k; i++) {
        string p;
        cin >> p;
        ac.add(p, i);
    }
    ac.build();
    cout << count_avoid_pow(ac, len).val() << '\n';
}
