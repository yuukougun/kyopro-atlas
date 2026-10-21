// 値で位置を指定する双方向リスト：「値 x の直後に y を挿入」「値 x を削除」を繰り返し、最後の列を出力する。
// 値は 1 以上で互いに異なるとし、値が大きくても扱えるよう前後の値を map で持つ。
// 入力：n と初期の列、q と各操作（"1 x y"：x の直後に y を挿入、"2 x"：x を削除）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    const long long HEAD = 0, TAIL = -1;  // 番兵：列に現れない値を先頭と末尾に置く
    map<long long, long long> nxt, prv;    // nxt[v]：v の次の値、prv[v]：v の前の値

    // x の直後に y を入れる。x の次 z を先に読んでから、4 本のつながりを書き換える
    auto insert_after = [&](long long x, long long y) {
        long long z = nxt[x];
        nxt[x] = y, prv[y] = x;
        nxt[y] = z, prv[z] = y;
    };
    // x を外す。前 p と次 n を直接つなぎ、x の行は消す（消した x の nxt・prv を後で読まない）
    auto erase = [&](long long x) {
        long long p = prv[x], n = nxt[x];
        nxt[p] = n, prv[n] = p;
        nxt.erase(x), prv.erase(x);
    };
    // --8<-- [end:core]

    nxt[HEAD] = TAIL, prv[TAIL] = HEAD;  // 空の列は HEAD → TAIL
    int n;
    cin >> n;
    long long last = HEAD;  // 初期の列は末尾に足していく
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        assert(a >= 1 && !nxt.count(a));
        insert_after(last, a);
        last = a;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            long long x, y;
            cin >> x >> y;
            assert(nxt.count(x) && x != TAIL && y >= 1 && !nxt.count(y));
            insert_after(x, y);
        } else {
            long long x;
            cin >> x;
            assert(x >= 1 && nxt.count(x));
            erase(x);
        }
    }

    // --8<-- [start:output]
    // 先頭の番兵の次から、末尾の番兵に着くまで nxt をたどる
    vector<long long> res;
    for (long long v = nxt[HEAD]; v != TAIL; v = nxt[v]) {
        assert(prv[nxt[v]] == v);  // 保つ性質：prv[nxt[v]] = v
        res.push_back(v);
    }
    // --8<-- [end:output]
    for (int i = 0; i < (int)res.size(); i++) cout << res[i] << (i + 1 < (int)res.size() ? " " : "");
    cout << '\n';
}
