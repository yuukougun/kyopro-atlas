// 箱ごとの色の集合を、小さい方を大きい方へ移して併合する
// 入力：N Q、C_0 … C_{N-1}（箱 i に最初に入っている 1 個の色）、続く Q 行は「a b」（箱 a の中身をすべて箱 b へ移す）
// 出力：各操作の後の、箱 b の色の種類数
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 箱 a の中身をすべて箱 b へ移す。s[i] は箱 i に入っている色の集合
void move_all(vector<set<int>>& s, int a, int b) {
    if (a == b) return;                       // 自分へ移すと、下の clear で中身が消える
    if (s[a].size() > s[b].size()) {
        swap(s[a], s[b]);                     // 中身だけを O(1) で入れ替え、b が大きい方を持つ
    }
    for (int c : s[a]) s[b].insert(c);        // 小さい方の要素だけを 1 つずつ移す
    s[a].clear();
}
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<set<int>> s(n);
    vector<multiset<int>> naive(n);  // 素朴な方法で答えを確かめる
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        s[i].insert(c);
        naive[i].insert(c);
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        move_all(s, a, b);
        if (a != b) {
            for (int c : naive[a]) naive[b].insert(c);
            naive[a].clear();
        }
        assert(s[b] == set<int>(naive[b].begin(), naive[b].end()));
        assert(s[a].empty() || a == b);
        cout << s[b].size() << '\n';
    }
}
