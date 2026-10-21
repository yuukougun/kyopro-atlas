// 根に成分の情報を持たせる：各成分の頂点番号の上位 K 個（大きい順）を根にだけ持ち、併合で合成する。
// クエリ "1 u v"：u と v を結ぶ辺を足す。"2 v k"：v の成分で k 番目に大きい頂点番号（なければ -1）。
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    const int K = 10;
    int n, q;
    cin >> n >> q;
    atcoder::dsu d(n);
    // top[r]：r が根のときだけ意味を持つ。成分の頂点番号の上位 K 個（降順）
    vector<vector<int>> top(n);
    for (int v = 0; v < n; v++) top[v] = {v};

    // --8<-- [start:core]
    auto unite = [&](int a, int b) {
        int ra = d.leader(a), rb = d.leader(b);  // 併合の前に両方の根を取る
        if (ra == rb) return;                      // 同じ成分なら情報は変わらない
        int r = d.merge(ra, rb);                   // 新しい根（大きい方の成分の根）
        int c = (r == ra) ? rb : ra;               // 根でなくなった方
        vector<int> merged;
        merge(top[r].begin(), top[r].end(), top[c].begin(), top[c].end(),
              back_inserter(merged), greater<int>());  // 降順の 2 列を 1 列に
        if ((int)merged.size() > K) merged.resize(K);   // 上位 K 個だけ残す
        top[r] = move(merged);
        top[c].clear();  // 古い根の情報は使わない（メモリも返す）
    };
    auto kth = [&](int v, int k) -> int {  // k は 1 始まり
        const vector<int>& t = top[d.leader(v)];  // 必ず根の情報を見る
        return k <= (int)t.size() ? t[k - 1] : -1;
    };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int type, x, y;
        cin >> type >> x >> y;
        assert(0 <= x && x < n);
        if (type == 1) {
            assert(0 <= y && y < n);
            unite(x, y);
        } else {
            assert(1 <= y && y <= K);
            cout << kth(x, y) << '\n';
        }
    }
}
