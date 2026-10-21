// 1 以上 2^n 未満の各整数 v を値段 c[v] で買える。買った数の XOR で 1 以上 2^n 未満のすべての値を
// 作れるようにするときの、値段の和の最小値。入力：n、c[1..2^n-1]。出力：最小値。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int full = 1 << n;
    vector<long long> c(full, 0);
    for (int v = 1; v < full; v++) cin >> c[v];

    // --8<-- [start:core]
    vector<int> order;
    for (int v = 1; v < full; v++) order.push_back(v);
    ranges::sort(order, [&](int x, int y) { return c[x] < c[y]; });  // 安い順

    vector<int> b(n, 0);  // b[i]：最上位 bit が i の基底の要素
    long long total = 0;
    for (int v : order) {
        int x = v;
        for (int i = n - 1; i >= 0; i--) {
            if ((x >> i & 1) == 0) continue;
            if (b[i] == 0) {
                b[i] = x;
                total += c[v];  // 基底に入った（今までの数で作れない）ものだけ買う
                break;
            }
            x ^= b[i];
        }
    }
    cout << total << '\n';
    // --8<-- [end:core]

    // n が小さければ、買う集合をすべて試して比べる
    if (full - 1 <= 15) {
        long long best = LLONG_MAX;
        for (int s = 0; s < (1 << (full - 1)); s++) {
            vector<bool> made(full, false);
            made[0] = true;
            long long cost = 0;
            for (int v = 1; v < full; v++) {
                if ((s >> (v - 1) & 1) == 0) continue;
                cost += c[v];
                vector<bool> nxt = made;
                for (int x = 0; x < full; x++) {
                    if (made[x]) nxt[x ^ v] = true;
                }
                made = nxt;
            }
            if (ranges::count(made, true) == full) best = min(best, cost);
        }
        assert(best == total);
    }
}
