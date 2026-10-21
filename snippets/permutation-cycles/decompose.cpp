// 置換の巡回分解：i → p[i] を訪問済みの印を付けてたどり、巡回の列を作る。
// 巡回の個数 c と、任意の 2 要素の swap でソートする最小回数 n − c を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;  // 入力は 1-indexed なので 0-indexed に直す
    }
    {
        vector<int> sorted_p = p;
        sort(sorted_p.begin(), sorted_p.end());
        for (int i = 0; i < n; i++) assert(sorted_p[i] == i);  // 順列であること
    }

    // --8<-- [start:core]
    vector<vector<int>> cycles;      // 各巡回の頂点を、たどった順に持つ
    vector<int> cyc_id(n), pos(n);   // i が属する巡回の番号と、その中での位置
    vector<bool> seen(n, false);
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;       // すでにどこかの巡回に入っている
        vector<int> cyc;
        for (int v = s; !seen[v]; v = p[v]) {  // s に戻るまでたどる
            seen[v] = true;
            cyc_id[v] = cycles.size();
            pos[v] = cyc.size();
            cyc.push_back(v);
        }
        cycles.push_back(cyc);
    }
    int c = cycles.size();
    cout << c << ' ' << n - c << '\n';  // 巡回の個数と、swap の最小回数
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) {  // 位置の情報の自己検査：次の頂点は巡回の中の次の位置
        const vector<int>& cyc = cycles[cyc_id[v]];
        assert(cyc[pos[v]] == v);
        assert(cyc[(pos[v] + 1) % cyc.size()] == p[v]);
    }
}
