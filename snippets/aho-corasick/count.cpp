// Aho-Corasick 法の構築と、各パターンの出現回数の集計
// 入力：S、Q、T_1 … T_Q（どれも英小文字で空でない）。出力：各 T_i の S の中での出現回数
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct AhoCorasick {
    // 節点 0 が根。nxt[v][c] は、build の前は Trie の子（なければ -1）、
    // build の後は「節点 v で文字 c を読んだ後の節点」（すべて埋まる）
    vector<array<int, 26>> nxt;
    vector<int> link;   // 失敗リンク：v の文字列の真の接尾辞のうち、Trie にある最長のもの
    vector<int> term;   // build の後は「v の文字列の接尾辞に、どれかのパターンがあるか」
    vector<int> order;  // BFS 順に並べた節点（根が先頭）

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
    // add_node・insert（Trie への追加と終端の印）は Trie のページと同じなので省く
// --8<-- [end:core]

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
};

// --8<-- [start:count]
// cnt[v] = S を流したときに節点 v に止まった回数。失敗リンクの木で葉から根へ足すと、
// cnt[v] は「v の文字列が S に現れる回数」になる
vector<long long> count_occurrences(const AhoCorasick& ac, const string& s) {
    vector<long long> cnt(ac.nxt.size(), 0);
    int v = 0;
    for (char ch : s) {
        v = ac.nxt[v][ch - 'a'];
        cnt[v]++;
    }
    for (int i = (int)ac.order.size() - 1; i >= 1; i--) {  // BFS の逆順なら子が親より先
        int u = ac.order[i];
        cnt[ac.link[u]] += cnt[u];
    }
    return cnt;
}
// --8<-- [end:count]

int main() {
    string s;
    int q;
    cin >> s >> q;
    vector<string> t(q);
    AhoCorasick ac;
    vector<int> node(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i];
        node[i] = ac.insert(t[i]);
    }
    ac.build();
    auto cnt = count_occurrences(ac, s);
    for (int i = 0; i < q; i++) {
        long long naive = 0;  // 確かめ用
        for (size_t p = 0; p + t[i].size() <= s.size(); p++) naive += s.compare(p, t[i].size(), t[i]) == 0;
        assert(cnt[node[i]] == naive);
        cout << cnt[node[i]] << '\n';
    }
}
