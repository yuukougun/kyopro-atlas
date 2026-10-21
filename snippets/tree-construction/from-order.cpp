// 訪問順から木を数える：頂点 0 から始め、訪問済みの頂点に隣接する未訪問の頂点のうち番号が最小のものを
// 次に訪れる規則で、訪問順が q になる N 頂点のラベル付きの木の個数を 998244353 で割った余りで求める。
// 位置 i の頂点の親になれるのは、位置 L..i-1 の頂点（L は i より左で q[i] より大きい最後の位置、なければ 0）。
// 入力：N、q_0 … q_{N-1}（0..N-1 の順列）。出力：個数
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<int> q(n);
    for (int i = 0; i < n; i++) cin >> q[i];

    // --8<-- [start:core]
    mint ans = (q[0] == 0 ? 1 : 0);  // 根（頂点 0）が最初でなければ 0 通り
    vector<int> st;                  // 位置の列。値が左から右へ減る（単調スタック）
    for (int i = 0; i < n; i++) {
        while (!st.empty() && q[st.back()] < q[i]) st.pop_back();
        int l = st.empty() ? 0 : st.back();  // q[i] より大きい最後の位置
        if (i > 0) ans *= i - l;             // 親の候補は位置 l, l+1, …, i-1
        st.push_back(i);
    }
    // --8<-- [end:core]

    cout << ans.val() << '\n';
}
