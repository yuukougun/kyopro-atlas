// 木を頂点数 k のパスに分けられるかを、葉から未完成のパスの長さを親へ送って判定する。
// 入力：n k、続いて辺 n - 1 本（1-indexed、n は k の倍数）。出力：Yes か No。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
bool split_into_paths(int n, int k, const vector<vector<int>>& g) {
    // 根を 0 にした BFS 順。逆順に見れば子が親より先に来る（再帰を使わない）
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            order.push_back(c);
        }
    }
    // up[v]：v から親へ伸びる未完成のパスの頂点数（0 なら v の部分木で閉じた）
    vector<int> up(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        int cnt = 0, sum = 0;  // 未完成のまま届いた子の数と、その頂点数の和
        for (int c : g[v]) {
            if (c == par[v] || up[c] == 0) continue;
            cnt++;
            sum += up[c];
        }
        int len = sum + 1;  // v を足した長さ
        if (cnt >= 3 || len > k) return false;    // 3 本は 1 本のパスにならない
        if (cnt == 2 && len != k) return false;   // 2 本をつなぐとそれ以上伸ばせない
        up[v] = (len == k) ? 0 : len;             // ちょうど k なら閉じて切り離す
    }
    return up[0] == 0;
}
// --8<-- [end:core]

int main() {
    int n, k;
    cin >> n >> k;
    assert(n >= 1 && k >= 1 && n % k == 0);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cout << (split_into_paths(n, k, g) ? "Yes" : "No") << '\n';
}
