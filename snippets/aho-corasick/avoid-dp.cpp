// どのパターンも含まない長さ L の英小文字列の数（mod 998244353）
// 入力：K L、P_1 … P_K（英小文字で空でない）。出力：個数
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

struct AhoCorasick {
    // 節点 0 が根。nxt[v][c] は、build の前は Trie の子（なければ -1）、
    // build の後は「節点 v で文字 c を読んだ後の節点」（すべて埋まる）
    vector<array<int, 26>> nxt;
    vector<int> link;   // 失敗リンク：v の文字列の真の接尾辞のうち、Trie にある最長のもの
    vector<int> term;   // build の後は「v の文字列の接尾辞に、どれかのパターンがあるか」
    vector<int> order;  // BFS 順に並べた節点（根が先頭）

    AhoCorasick() { add_node(); }

    int add_node() {
        array<int, 26> a;
        a.fill(-1);
        nxt.push_back(a);
        link.push_back(0);
        term.push_back(0);
        return (int)nxt.size() - 1;
    }

    int insert(const string& s) {  // s の終端の節点を返す
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                int u = add_node();
                nxt[v][c] = u;
            }
            v = nxt[v][c];
        }
        term[v] = 1;
        return v;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            order.push_back(v);
            if (v != 0 && term[link[v]]) term[v] = 1;  // 印を失敗リンク先から受け継ぐ
            for (int c = 0; c < 26; c++) {
                int u = nxt[v][c];
                int w = (v == 0 ? 0 : nxt[link[v]][c]);  // link[v] の行は v より先に埋まっている
                if (u == -1) {
                    nxt[v][c] = w;  // 子がなければ、失敗した先の遷移を写す
                } else {
                    link[u] = w;    // 子の失敗リンクは、親の失敗リンク先から c で進んだ先
                    q.push(u);
                }
            }
        }
    }
};

int main() {
    int k, len;
    cin >> k >> len;
    AhoCorasick ac;
    for (int i = 0; i < k; i++) {
        string p;
        cin >> p;
        ac.insert(p);
    }
    ac.build();
    int m = ac.nxt.size();
    // --8<-- [start:dp]
    vector<mint> dp(m, 0);  // dp[v] = いまの節点が v で、まだどのパターンも含まない文字列の数
    dp[0] = 1;
    for (int step = 0; step < len; step++) {
        vector<mint> ndp(m, 0);
        for (int v = 0; v < m; v++) {
            if (dp[v] == 0) continue;
            for (int c = 0; c < 26; c++) {
                int u = ac.nxt[v][c];
                if (!ac.term[u]) ndp[u] += dp[v];  // 受け継いだ印で判定する
            }
        }
        dp = ndp;
    }
    mint ans = 0;
    for (int v = 0; v < m; v++) ans += dp[v];
    // --8<-- [end:dp]
    cout << ans.val() << '\n';
}
