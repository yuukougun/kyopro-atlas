#include <bits/stdc++.h>
using namespace std;

// 反転フラグつきの deque。
// 保つ性質：rev が false なら d の並びが実際の列、true なら d を逆から読んだものが実際の列
struct FlipDeque {
    deque<int> d;
    bool rev = false;
    // --8<-- [start:core]
    void reverse_all() { rev = !rev; }
    void push_front(int x) {          // 実際の先頭は、rev のとき d の末尾
        if (!rev) d.push_front(x);
        else d.push_back(x);
    }
    void push_back(int x) {
        if (!rev) d.push_back(x);
        else d.push_front(x);
    }
    int at(int i) const {             // 実際の i 番目（0-indexed）
        return !rev ? d[i] : d[d.size() - 1 - i];
    }
    vector<int> finish() const {      // 最後に向きを直す
        vector<int> res(d.begin(), d.end());
        if (rev) reverse(res.begin(), res.end());
        return res;
    }
    // --8<-- [end:core]
};

int main() {
    // 入力：Q と、Q 行の操作。"R"（反転）・"F x"（先頭に追加）・"B x"（末尾に追加）・"G i"（i 番目を出力）
    // 最後に列全体を 1 行で出力する
    int q;
    cin >> q;
    FlipDeque fd;
    for (int k = 0; k < q; k++) {
        char t;
        cin >> t;
        if (t == 'R') {
            fd.reverse_all();
        } else if (t == 'F') {
            int x;
            cin >> x;
            fd.push_front(x);
        } else if (t == 'B') {
            int x;
            cin >> x;
            fd.push_back(x);
        } else {
            int i;
            cin >> i;
            assert(0 <= i && i < (int)fd.d.size());
            cout << fd.at(i) << '\n';
        }
    }
    vector<int> res = fd.finish();
    for (int i = 0; i < (int)res.size(); i++) {
        cout << res[i] << (i + 1 == (int)res.size() ? "" : " ");
    }
    cout << '\n';
}
