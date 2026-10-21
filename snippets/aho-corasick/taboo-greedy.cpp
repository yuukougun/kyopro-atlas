// S の文字を最少個数だけ * に変えて、どの T_i も部分文字列に含まないようにする
// 入力：S、N、T_1 … T_N（英小文字で空でない）。出力：最少の個数
#include <bits/stdc++.h>
using namespace std;

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
    string s;
    int n;
    cin >> s >> n;
    vector<string> t(n);
    AhoCorasick ac;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        ac.insert(t[i]);
    }
    ac.build();
    // --8<-- [start:greedy]
    int ans = 0, v = 0;
    for (char ch : s) {
        v = ac.nxt[v][ch - 'a'];
        if (ac.term[v]) {  // ここで終わる出現がある：この文字を * にする
            ans++;
            v = 0;         // * をまたぐ出現はないので、根からやり直す
        }
    }
    // --8<-- [end:greedy]
    // 確かめ用：出現を区間 [l, r] として、右端の小さい順に串刺しにする
    vector<pair<int, int>> iv;  // (r, l)
    for (int i = 0; i < n; i++)
        for (size_t p = 0; p + t[i].size() <= s.size(); p++)
            if (s.compare(p, t[i].size(), t[i]) == 0) iv.push_back({(int)(p + t[i].size()) - 1, (int)p});
    sort(iv.begin(), iv.end());
    int naive = 0, last = -1;
    for (auto [r, l] : iv)
        if (l > last) {
            naive++;
            last = r;
        }
    assert(ans == naive);
    cout << ans << '\n';
}
