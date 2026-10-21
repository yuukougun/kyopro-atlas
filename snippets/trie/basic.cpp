#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Trie {
    // 節点 0 が根。nxt[v][c] は子の番号（なければ -1）
    vector<array<int, 26>> nxt;
    vector<int> cnt;  // 通過数：この節点を通る（この接頭辞を持つ）文字列の数
    vector<int> ed;   // 終端の数：ちょうどこの節点で終わる文字列の数

    Trie() { add_node(); }

    int add_node() {
        array<int, 26> a;
        a.fill(-1);
        nxt.push_back(a);
        cnt.push_back(0);
        ed.push_back(0);
        return (int)nxt.size() - 1;
    }

    // s を d 個（d = 1 で追加、d = -1 で削除）だけ入れ、終端の節点を返す
    int insert(const string& s, int d = 1) {
        int v = 0;
        cnt[v] += d;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                int u = add_node();  // push_back の後なので、ここより前に取った参照は使わない
                nxt[v][c] = u;
            }
            v = nxt[v][c];
            cnt[v] += d;
        }
        ed[v] += d;
        return v;
    }

    // p の節点の番号（なければ -1）
    int find(const string& p) const {
        int v = 0;
        for (char ch : p) {
            v = nxt[v][ch - 'a'];
            if (v == -1) return -1;
        }
        return v;
    }

    int count_prefix(const string& p) const {  // p を接頭辞に持つ文字列の数
        int v = find(p);
        return v == -1 ? 0 : cnt[v];
    }
    int count_exact(const string& s) const {  // s に等しい文字列の数
        int v = find(s);
        return v == -1 ? 0 : ed[v];
    }
};
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    Trie t;
    multiset<string> naive;  // 確かめ用
    for (int i = 0; i < q; i++) {
        int op;
        string s;
        cin >> op >> s;
        if (op == 1) {
            t.insert(s, 1);
            naive.insert(s);
        } else if (op == 2) {  // s が入っていることを仮定する
            assert(naive.count(s) > 0);
            t.insert(s, -1);
            naive.erase(naive.find(s));
        } else if (op == 3) {
            int ans = t.count_prefix(s);
            int ex = 0;
            for (const string& x : naive) ex += x.compare(0, s.size(), s) == 0 && x.size() >= s.size();
            assert(ans == ex);
            cout << ans << '\n';
        } else {
            int ans = t.count_exact(s);
            assert(ans == (int)naive.count(s));
            cout << ans << '\n';
        }
    }
    // 節点数は (入れた長さの総和) + 1 以下
    return 0;
}
