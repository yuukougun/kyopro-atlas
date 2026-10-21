// 文字の集合を 26 ビットで持ち、OR のセグメント木に載せる
// 入力：N、英小文字の文字列 S、Q、続く Q 行は「0 i c」（S[i] を c にする）か「1 l r」（S[l, r) の文字の種類数を出力）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
int op(int a, int b) { return a | b; }  // 集合の和
int e() { return 0; }                   // 空集合
int bit(char c) { return 1 << (c - 'a'); }  // 1 文字だけの集合

// 葉 i を bit(S[i]) にして作る
// 更新：seg.set(i, bit(c))
// 種類数：popcount((unsigned)seg.prod(l, r))
// --8<-- [end:core]

int main() {
    int n, q;
    string s;
    cin >> n >> s >> q;
    vector<int> leaf(n);
    for (int i = 0; i < n; i++) leaf[i] = bit(s[i]);
    atcoder::segtree<int, op, e> seg(leaf);
    for (int k = 0; k < q; k++) {
        int t;
        cin >> t;
        if (t == 0) {
            int i;
            char c;
            cin >> i >> c;
            s[i] = c;
            seg.set(i, bit(c));
        } else {
            int l, r;
            cin >> l >> r;
            int res = popcount((unsigned)seg.prod(l, r));
            set<char> naive(s.begin() + l, s.begin() + r);  // 素朴に数えて確かめる
            assert(res == (int)naive.size());
            cout << res << '\n';
        }
    }
}
