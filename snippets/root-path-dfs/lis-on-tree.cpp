// 根から各頂点へのパス上の値の列について、狭義の LIS の長さを求める。
// 二分探索版の配列 L（L[k] = 長さ k + 1 の増加列の末尾の最小値）を 1 本だけ持ち、
// 入るときの 1 か所の変更を「位置と元の値」として記録し、出るときに記録から戻す。
// 確かめのため、パスの列を持つ素朴な DFS（O(長さ^2) の LIS）と答えが一致することを assert する。
// 入力は N、値 a_1 … a_N、辺 N − 1 本（1-indexed）。根は頂点 1。出力は各頂点の答え。
#include <bits/stdc++.h>
using namespace std;

int naive_lis(const vector<long long>& s) {
    int m = s.size(), best = 0;
    vector<int> f(m, 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if (s[j] < s[i]) f[i] = max(f[i], f[j] + 1);
        }
        best = max(best, f[i]);
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    vector<long long> L;     // 根から今の頂点までの列の、二分探索版の LIS の配列
    vector<int> ans(n);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        // 入る：L の 1 か所だけを変え、戻すための記録（位置・元の値）を残す
        int pos = lower_bound(L.begin(), L.end(), a[v]) - L.begin();
        bool appended = (pos == (int)L.size());
        long long old = appended ? 0 : L[pos];
        if (appended) L.push_back(a[v]);
        else L[pos] = a[v];
        ans[v] = L.size();

        for (int to : g[v]) {
            if (to != p) self(self, to, v);
        }

        // 出る：記録から元に戻す（子孫の変更はすべて戻った後なので、L は入った直後の形）
        if (appended) L.pop_back();
        else L[pos] = old;
    };
    dfs(dfs, 0, -1);
    // --8<-- [end:core]
    assert(L.empty());

    vector<long long> path;  // 根から今の頂点までの値
    auto check = [&](auto&& self, int v, int p) -> void {
        path.push_back(a[v]);
        assert(ans[v] == naive_lis(path));
        for (int to : g[v]) {
            if (to != p) self(self, to, v);
        }
        path.pop_back();
    };
    check(check, 0, -1);

    for (int v = 0; v < n; v++) cout << ans[v] << '\n';
}
