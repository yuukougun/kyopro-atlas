// 文字列 S と Q 個の文字列 T について、T が S の部分列かを判定する。
// nxt[i][c] は位置 i 以降で文字 c が最初に現れる位置（なければ番兵 N）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<array<int, 26>> build_next(const string& s) {
    int n = s.size();
    vector<array<int, 26>> nxt(n + 1);
    nxt[n].fill(n);  // 番兵の行：どの文字も「見つからない」
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];  // 位置 i より後ろの答えを写し
        nxt[i][s[i] - 'a'] = i;  // S[i] の文字だけ i に更新する
    }
    return nxt;
}

// 位置 p から T を貪欲に照合し、最後の文字を拾った位置を返す（照合できなければ n）
int match_end(const vector<array<int, 26>>& nxt, const string& t, int p = 0) {
    int n = nxt.size() - 1;
    int last = p - 1;  // p：次に探し始める位置
    for (char ch : t) {
        int q = nxt[p][ch - 'a'];
        if (q == n) return n;
        last = q;
        p = q + 1;  // 拾った位置は使ったので、その次から探す
    }
    return last;
}
// --8<-- [end:core]

int main() {
    string s;
    int q;
    cin >> s >> q;
    auto nxt = build_next(s);
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        cout << (match_end(nxt, t) < (int)s.size() ? "Yes" : "No") << '\n';
    }
}
