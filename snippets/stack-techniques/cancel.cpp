// 打ち消し：文字列 s から、t と一致する部分を見つけたら取り除く操作を、できなくなるまで繰り返す。
// 結果の文字列をスタック（string）として左から作り、末尾が t になったらその場で取り除く。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    assert(!t.empty());

    // --8<-- [start:core]
    string res;  // スタック：取り除けるものを取り除いた後の、ここまでの結果
    int m = t.size();
    for (char c : s) {
        res.push_back(c);
        // 新しく t ができるなら、それは末尾にしかない
        if ((int)res.size() >= m && res.compare(res.size() - m, m, t) == 0) {
            res.resize(res.size() - m);  // 末尾の m 文字を取り除く
        }
    }
    // --8<-- [end:core]
    cout << res << '\n';
}
