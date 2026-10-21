// 障害物の 8 近傍の連結による判定：H×W のグリッド（行 1..H、列 1..W）に障害物が K 個ある。
// 上下左右の移動で (1, 1) から (H, W) へ行けるかを、マスを全部見ずに O(K log K) で判定する。
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    long long h, w;
    int k;
    cin >> h >> w >> k;
    vector<long long> r(k), c(k);
    for (int i = 0; i < k; i++) cin >> r[i] >> c[i];
    for (int i = 0; i < k; i++) assert(1 <= r[i] && r[i] <= h && 1 <= c[i] && c[i] <= w);

    // --8<-- [start:core]
    // 障害物 i を頂点 i に、仮想の頂点 A = k（左端か下端）、B = k + 1（右端か上端）を足す
    map<pair<long long, long long>, int> id;  // 座標 → 障害物の番号（H×W の配列は作れない）
    for (int i = 0; i < k; i++) id[{r[i], c[i]}] = i;
    atcoder::dsu uf(k + 2);
    const int A = k, B = k + 1;
    for (int i = 0; i < k; i++) {
        if (c[i] == 1 || r[i] == h) uf.merge(i, A);
        if (c[i] == w || r[i] == 1) uf.merge(i, B);
        for (int dr = -1; dr <= 1; dr++)  // 斜めを含む 8 近傍の障害物とつなぐ
            for (int dc = -1; dc <= 1; dc++) {
                auto it = id.find({r[i] + dr, c[i] + dc});
                if (it != id.end()) uf.merge(i, it->second);
            }
    }
    // A と B が障害物の鎖でつながると、左上と右下は分断される
    cout << (uf.same(A, B) ? "No" : "Yes") << '\n';
    // --8<-- [end:core]
}
