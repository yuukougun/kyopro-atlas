#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct SuffixAutomaton {
    struct State {
        int len = 0;    // この状態に属す最長の部分文字列の長さ
        int link = -1;  // 接尾辞リンク（状態 0 は -1）
        array<int, 26> next;
        State() { next.fill(-1); }
    };
    vector<State> st{State()};  // 状態 0 は空文字列
    int last = 0;               // 文字列全体を含む状態

    // 文字 c を末尾に足し、新しく増えた異なる部分文字列の数を返す
    long long extend(int c) {
        int cur = st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);  // 遷移とリンクを写す
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = clone;
                st[cur].link = clone;
            }
        }
        last = cur;
        return st[cur].len - st[st[cur].link].len;
    }
};
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    SuffixAutomaton sam;
    long long distinct = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        distinct += sam.extend(s[i] - 'a');
        cout << distinct << (i + 1 == n ? '\n' : ' ');
    }
    // 状態ごとの len - len(link) の和も、異なる部分文字列の数になる
    long long total = 0;
    int transitions = 0;
    for (int v = 1; v < (int)sam.st.size(); v++) {
        total += sam.st[v].len - sam.st[sam.st[v].link].len;
    }
    for (auto& x : sam.st) {
        for (int t : x.next) transitions += (t != -1);
    }
    assert(total == distinct);
    if (n >= 2) assert((int)sam.st.size() <= 2 * n - 1);
    if (n >= 3) assert(transitions <= 3 * n - 4);
    cout << sam.st.size() << ' ' << transitions << '\n';
}
