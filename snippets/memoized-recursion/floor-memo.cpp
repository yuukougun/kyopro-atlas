// まばらな状態のメモ化：f(0) = 0、f(n) = max(n, f(⌊n/2⌋) + f(⌊n/3⌋) + f(⌊n/4⌋)) を n ≤ 10^17 で求める。
// 現れる値は ⌊n/(2^a 3^b)⌋ の形だけなので、配列ではなく map に覚えさせる。
// 出力：f(n) と、メモに入った状態の数。
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    assert(0 <= n && n <= 100000000000000000LL);

    // --8<-- [start:core]
    map<long long, long long> memo;  // memo に鍵があれば計算済み（値が 0 でも区別できる）
    auto f = [&](auto&& self, long long x) -> long long {
        if (x == 0) return 0;                       // 1. 終わりの値
        auto it = memo.find(x);                     // 2. 計算済みならそれを返す
        if (it != memo.end()) return it->second;    //    （memo[x] で調べると 0 の要素が入ってしまう）
        long long res = max(x, self(self, x / 2) + self(self, x / 3) + self(self, x / 4));  // 3. 漸化式
        memo[x] = res;                              // 4. 返す前に覚える
        return res;
    };
    cout << f(f, n) << ' ' << memo.size() << '\n';
    // --8<-- [end:core]
}
