// i = 1, 2, …, N の順に i を先頭から P_i 番目へ挿入した後の列を、逆順の処理で求める
// 入力：N、P_1 … P_N（1 ≤ P_i ≤ i）
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> t;
    Fenwick(int n) : n(n), t(n + 1, 0) {}
    void add(int p, long long x) {
        for (int i = p + 1; i <= n; i += i & -i) t[i] += x;
    }
    int kth(long long k) {
        int pos = 0;
        for (int step = bit_floor((unsigned)n); step > 0; step >>= 1) {
            if (pos + step <= n && t[pos + step] < k) {
                k -= t[pos + step];
                pos += step;
            }
        }
        return pos;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    // --8<-- [start:core]
    Fenwick empty(n);                            // 空いている位置を 1 にする
    for (int j = 0; j < n; j++) empty.add(j, 1);
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {           // 後に挿入したものから位置を決める
        int j = empty.kth(p[i]);                 // 空きのうち p[i] 番目（p[i] は 1 始まり）
        ans[j] = i + 1;
        empty.add(j, -1);                        // 埋めた位置は空きでなくなる
    }
    // --8<-- [end:core]
    vector<int> naive;  // 素朴に挿入して確かめる（O(N^2)）
    for (int i = 0; i < n; i++) naive.insert(naive.begin() + (p[i] - 1), i + 1);
    assert(naive == ans);
    for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 < n ? ' ' : '\n');
}
