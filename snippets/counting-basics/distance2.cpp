// 一列に並んだ n 個を k 色で塗り、距離 2 以内（隣と 1 つおき）がすべて異なる色になる塗り方の数を
// 1000000007 で割った余りで求める。先頭から決めると選択肢は k, k-1, k-2, k-2, … と一定になる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

int main() {
    long long n, k;
    cin >> n >> k;
    assert(1 <= n && 1 <= k);

    // --8<-- [start:core]
    // 1 個目は k 通り、2 個目は 1 個目と違う k-1 通り、
    // 3 個目以降は直前の 2 個（互いに異なる）と違う k-2 通り。どれも前の選び方によらない
    mint ans;
    if (n == 1) {
        ans = mint(k);  // 指数 n-2 が負になるので分ける
    } else {
        // k(k-1) は 10^18 近くになり、続けて掛けるとあふれるので、mint にしてから掛ける（mint(k-2) は k=1 で -1 だが、k-1=0 が掛かる）
        ans = mint(k) * mint(k - 1) * mint(k - 2).pow(n - 2);
    }
    cout << ans.val() << '\n';
    // --8<-- [end:core]
}
