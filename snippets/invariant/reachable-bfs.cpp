#include <bits/stdc++.h>
using namespace std;

// 長さ n の列で「隣り合う 2 つの符号を反転する」操作を何度でも行うとき、
// すべて正の状態から届く符号の並びを全探索で数え、
// 「負の個数の偶奇が変わらない」という予想と一致するかを確かめる。
int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    // 状態は負の位置を 1 にした bit 列。小さい n なら 2^n 通りを全部たどれる
    vector<bool> seen(1 << n, false);
    queue<int> que;
    seen[0] = true;
    que.push(0);
    while (!que.empty()) {
        int s = que.front();
        que.pop();
        for (int i = 0; i + 1 < n; i++) {
            int t = s ^ (0b11 << i);  // i 番目と i + 1 番目の符号を反転する
            if (!seen[t]) {
                seen[t] = true;
                que.push(t);
            }
        }
    }
    int reachable = 0;
    for (int s = 0; s < (1 << n); s++) {
        bool even = __builtin_popcount(s) % 2 == 0;
        if (seen[s]) reachable++;
        // 予想：届く ⇔ 負の個数が偶数（ただし n = 1 は操作できない）
        if (n >= 2) assert(seen[s] == even);
    }
    // --8<-- [end:core]
    cout << reachable << '\n';
    return 0;
}
