#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:table]
// c[i][k]（符号なし第 1 種スターリング数）の表を漸化式で埋める。O(n^2)
vector<vector<mint>> stirling_table(int n) {
    vector<vector<mint>> c(n + 1, vector<mint>(n + 1));
    c[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= i; k++) {
            // 要素 i が 1 人で新しい巡回を作る + 既存の i - 1 個のどれかの直後に入る
            c[i][k] = c[i - 1][k - 1] + mint(i - 1) * c[i - 1][k];
        }
    }
    return c;
}
// --8<-- [end:table]

// --8<-- [start:core]
// x(x+1)...(x+n-1) を展開し、係数 c(n,0), ..., c(n,n) を返す。O(n log^2 n)
vector<mint> stirling_row(int n) {
    // (x+l)(x+l+1)...(x+r-1) を、半分ずつに分けて掛ける
    auto prod = [&](auto&& self, int l, int r) -> vector<mint> {
        if (r - l == 1) return {mint(l), mint(1)};
        int m = (l + r) / 2;
        return atcoder::convolution(self(self, l, m), self(self, m, r));
    };
    if (n == 0) return {mint(1)};  // 空の積は 1
    return prod(prod, 0, n);
}
// --8<-- [end:core]

int main() {
    // 全列挙：巡回の個数と、左から見える位置（それまでの最大値を更新する位置）の個数
    for (int n = 0; n <= 7; n++) {
        vector<long long> by_cycles(n + 1), by_records(n + 1);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            vector<bool> seen(n);
            int cycles = 0;
            for (int s = 0; s < n; s++) {
                if (seen[s]) continue;
                cycles++;
                for (int v = s; !seen[v]; v = p[v]) seen[v] = true;
            }
            int records = 0, mx = -1;
            for (int i = 0; i < n; i++) {
                if (p[i] > mx) { records++; mx = p[i]; }
            }
            by_cycles[cycles]++;
            by_records[records]++;
        } while (next_permutation(p.begin(), p.end()));
        auto c = stirling_table(n);
        for (int k = 0; k <= n; k++) {
            assert(c[n][k].val() == by_cycles[k]);
            assert(c[n][k].val() == by_records[k]);
        }
    }
    // 分割統治の積と漸化式の表が一致する
    auto t = stirling_table(100);
    for (int n = 0; n <= 100; n++) {
        auto row = stirling_row(n);
        assert((int)row.size() == n + 1);
        for (int k = 0; k <= n; k++) assert(row[k] == t[n][k]);
    }

    int n;
    cin >> n;
    auto row = stirling_row(n);
    for (int k = 0; k <= n; k++) cout << row[k].val() << (k == n ? '\n' : ' ');
}
