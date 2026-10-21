// 版の木（永続スタック）：末尾の追加・末尾の削除・保存・読み込みを、木の頂点の移動で処理する
// 入力：Q、続く Q 行は「ADD x」「DELETE」「SAVE y」「LOAD z」。各操作の後に末尾の値（空なら -1）を出力する
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct VersionTree {
    vector<int> par;        // par[v]：頂点 v の親（根 0 の親は 0）
    vector<long long> val;  // val[v]：頂点 v の版の末尾の値（根は空の列で -1）
    int cur = 0;            // 今の版を表す頂点
    VersionTree() : par{0}, val{-1} {}
    void push_back(long long x) {  // 子を作って移る
        par.push_back(cur);
        val.push_back(x);
        cur = (int)par.size() - 1;
    }
    void pop_back() { cur = par[cur]; }  // 親へ戻る（根なら根のまま）
    long long back() const { return val[cur]; }
};
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    VersionTree vt;
    // --8<-- [start:save]
    map<long long, int> saved;  // 保存の名前 → 頂点。まだ保存していない名前は空の列（根 0）
    // --8<-- [end:save]
    for (int i = 0; i < q; i++) {
        string op;
        cin >> op;
        if (op == "ADD") {
            long long x;
            cin >> x;
            vt.push_back(x);
        } else if (op == "DELETE") {
            vt.pop_back();
        } else if (op == "SAVE") {
            long long y;
            cin >> y;
            saved[y] = vt.cur;
        } else {
            assert(op == "LOAD");
            long long z;
            cin >> z;
            auto it = saved.find(z);
            vt.cur = (it == saved.end() ? 0 : it->second);
        }
        cout << vt.back() << '\n';
    }
}
