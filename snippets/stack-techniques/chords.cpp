// 円を切り開く：円周上の 2n 個の点 1, …, 2n を結ぶ n 本の弦（端点はすべて異なる）に交差があるか。
// 点を番号順に読み、相手がスタックの先頭なら pop、そうでなければ push する。最後に空なら交差なし。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> partner(2 * n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;  // 0-indexed に直す
        partner[a] = b;
        partner[b] = a;
    }

    // --8<-- [start:core]
    vector<int> st;  // まだ閉じていない弦の、先に読んだ端点
    for (int p = 0; p < 2 * n; p++) {
        if (!st.empty() && st.back() == partner[p]) st.pop_back();  // 直前に開いた弦を閉じる
        else st.push_back(p);
    }
    bool crossing = !st.empty();  // 閉じられずに残ったら、どこかで弦が交差している
    // --8<-- [end:core]
    cout << (crossing ? "Yes" : "No") << '\n';
}
