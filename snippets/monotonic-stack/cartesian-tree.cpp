// Cartesian tree（最大値が根）：単調スタックで親・左の子・右の子を O(N) で作る
// 入力：N、A_0 … A_{N-1}。出力：各 i の親（根は -1）
// 同じ値は左にある方を上にする（降ろすのは a[top] < a[i] のときだけ）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct CartesianTree {
    int root;
    vector<int> par, lch, rch;  // ない子・根の親は -1
};

CartesianTree build(const vector<long long>& a) {
    int n = a.size();
    vector<int> par(n, -1), lch(n, -1), rch(n, -1), st;
    for (int i = 0; i < n; i++) {
        int last = -1;  // 最後に降ろした添字
        while (!st.empty() && a[st.back()] < a[i]) {
            last = st.back();
            st.pop_back();
        }
        if (last != -1) {  // 降ろした山は i の左の子になる
            lch[i] = last;
            par[last] = i;
        }
        if (!st.empty()) {  // i は残った top の右の子になる
            rch[st.back()] = i;
            par[i] = st.back();
        }
        st.push_back(i);
    }
    int root = st.empty() ? -1 : st[0];
    return {root, par, lch, rch};
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    CartesianTree t = build(a);
    // 最大値で割る再帰と比べる：区間 [l, r) の最大値（同じなら左）が親 p の子になる
    vector<int> naive(n, -2);
    auto rec = [&](auto&& self, int l, int r, int p) -> void {
        if (l >= r) return;
        int m = l;
        for (int i = l; i < r; i++) {
            if (a[i] > a[m]) m = i;
        }
        naive[m] = p;
        self(self, l, m, m);
        self(self, m + 1, r, m);
    };
    rec(rec, 0, n, -1);
    for (int i = 0; i < n; i++) {
        assert(t.par[i] == naive[i]);
        cout << t.par[i] << (i + 1 < n ? ' ' : '\n');
    }
    if (n > 0) assert(t.par[t.root] == -1);
}
