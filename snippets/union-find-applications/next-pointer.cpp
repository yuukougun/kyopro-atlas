// 次の空きへ飛ぶ Union-Find：長さ n のマスに、区間 [l, r) のまだ塗られていないマスだけを色 c で塗る
// 操作を順に行い、最後の色を出力する（塗られていないマスは 0）。各マスは一度しか塗られない。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> color(n, 0);

    // --8<-- [start:core]
    // nxt[i] をたどった先（根）が「i 以降で最初のまだ塗られていないマス」。n は番兵（常に空き）
    vector<int> nxt(n + 1);
    iota(nxt.begin(), nxt.end(), 0);
    auto find = [&](int x) {
        while (nxt[x] != x) {
            nxt[x] = nxt[nxt[x]];  // 経路を半分に縮める（再帰しないので深い鎖でも安全）
            x = nxt[x];
        }
        return x;
    };
    auto paint = [&](int l, int r, int c) {  // 半開区間 [l, r)
        for (int i = find(l); i < r; i = find(i)) {
            color[i] = c;
            nxt[i] = i + 1;  // 塗ったマスは右隣とつなぐ（根は必ず右側の空き）
        }
    };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        assert(0 <= l && l <= r && r <= n && c > 0);
        paint(l, r, c);
    }
    for (int i = 0; i < n; i++) cout << color[i] << (i + 1 < n ? ' ' : '\n');
}
