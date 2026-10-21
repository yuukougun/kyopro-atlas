// 2 種類の文字を一斉に入れ替える操作を何回でも行って、S を T にできるかを判定する。
// 文字の対応 S[i] → T[i] が、行き先も出どころも一意（全単射）なら Yes。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
bool can_transform(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    array<int, 26> to, from;  // to[c]：S の文字 c の行き先、from[d]：T の文字 d の出どころ
    to.fill(-1);
    from.fill(-1);
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a', d = t[i] - 'a';
        if (to[c] == -1 && from[d] == -1) {  // どちらも初めて：対応を登録する
            to[c] = d;
            from[d] = c;
        } else if (to[c] != d || from[d] != c) {
            return false;  // 1 つの文字が 2 つの文字に、または 2 つの文字が 1 つの文字になる
        }
    }
    return true;
}
// --8<-- [end:core]

int main() {
    string s, t;
    cin >> s >> t;
    cout << (can_transform(s, t) ? "Yes" : "No") << '\n';
}
