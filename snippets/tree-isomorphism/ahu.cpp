// 根付き木の部分木を同型で分類する（AHU 法。Library Checker の
// Rooted Tree Isomorphism Classification と同じ入出力）。
// 入力：N と、頂点 1..N-1 の親 p_i（p_i < i）。根は 0。
// 出力：種類数 K と、各頂点の部分木の名前（0 以上 K 未満）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) cin >> par[i];

    // --8<-- [start:core]
    // p_i < i なので、番号の大きい順に見れば子は親より先に名前が決まる
    vector<vector<int>> child_names(n);
    map<vector<int>, int> dict;  // 子の名前の多重集合（整列した列）→ 名前
    vector<int> name(n);
    for (int v = n - 1; v >= 0; v--) {
        vector<int>& c = child_names[v];
        sort(c.begin(), c.end());  // 多重集合なので順番をそろえる
        auto it = dict.find(c);
        if (it == dict.end()) it = dict.emplace(c, (int)dict.size()).first;
        name[v] = it->second;
        if (v > 0) child_names[par[v]].push_back(name[v]);
        vector<int>().swap(c);  // 使い終えた列のメモリを返す
    }
    // --8<-- [end:core]

    int k = dict.size();
    assert(k >= 1 && k <= n);
    cout << k << '\n';
    for (int i = 0; i < n; i++) cout << name[i] << (i + 1 < n ? ' ' : '\n');
}
