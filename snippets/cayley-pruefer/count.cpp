#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

const int MAX = 200000;
vector<mint> fact(MAX + 1), ifact(MAX + 1);

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) fact[i] = fact[i - 1] * i;
    ifact[MAX] = fact[MAX].inv();
    for (int i = MAX; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

// --8<-- [start:trees]
// 頂点 1〜n のラベル付き木の個数 n^(n-2)。n = 1 は 1 個（指数が負になるので分ける）
mint count_trees(int n) {
    if (n == 1) return 1;
    return mint(n).pow(n - 2);
}
// --8<-- [end:trees]

// --8<-- [start:degrees]
// 頂点 v の次数が d[v] の木の個数 (n-2)! / Π(d[v]-1)!。木がない次数列なら 0
mint count_with_degrees(const vector<int>& d) {
    int n = d.size();
    if (n == 1) return d[0] == 0 ? 1 : 0;
    long long sum = 0;
    for (int x : d) {
        if (x < 1) return 0;  // 次数 0 の頂点があると連結にならない（ifact[-1] も防ぐ）
        sum += x;
    }
    if (sum != 2LL * n - 2) return 0;
    mint res = fact[n - 2];
    for (int x : d) res *= ifact[x - 1];
    return res;
}
// --8<-- [end:degrees]

// --8<-- [start:components]
// 大きさ s[0], …, s[k-1] の連結成分に k-1 本の辺を足して全体を木にする方法の数
// N^(k-2) * Π s[i]（N は頂点の総数）。k = 1 なら足す辺はなく 1 通り
mint connect_components(const vector<int>& s) {
    int k = s.size();
    if (k == 1) return 1;
    long long n = 0;
    mint prod = 1;
    for (int x : s) {
        n += x;
        prod *= x;
    }
    return mint(n).pow(k - 2) * prod;
}
// --8<-- [end:components]

// 以下は小さい n で全探索と一致することを確かめる部分
int find_root(vector<int>& p, int x) { return p[x] == x ? x : p[x] = find_root(p, p[x]); }

// 頂点に 0..n-1 の番号を振ったとき、comp[v] の成分どうしを結ぶ k-1 本の辺の選び方で、
// 成分を縮めたグラフが木になるものを数える（comp がすべて違えば、n 頂点の木そのもの）
// deg_count には、全頂点の次数列ごとの個数を数える（comp がすべて違うときだけ使う）
long long brute(int n, const vector<int>& comp, int k, map<vector<int>, long long>* deg_count) {
    vector<pair<int, int>> cand;
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (comp[u] != comp[v]) cand.push_back({u, v});
    int m = cand.size();
    long long total = 0;
    vector<int> pick;
    auto rec = [&](auto&& self, int i) -> void {
        if ((int)pick.size() == k - 1) {
            vector<int> p(k);
            iota(p.begin(), p.end(), 0);
            for (int e : pick) {
                int a = find_root(p, comp[cand[e].first]), b = find_root(p, comp[cand[e].second]);
                if (a == b) return;  // 閉路ができる
                p[a] = b;
            }
            total++;
            if (deg_count) {
                vector<int> d(n);
                for (int e : pick) d[cand[e].first]++, d[cand[e].second]++;
                (*deg_count)[d]++;
            }
            return;
        }
        if (i == m || m - i < k - 1 - (int)pick.size()) return;
        pick.push_back(i);
        self(self, i + 1);
        pick.pop_back();
        self(self, i + 1);
    };
    rec(rec, 0);
    return total;
}

void self_check() {
    for (int n = 1; n <= 7; n++) {
        vector<int> comp(n);
        iota(comp.begin(), comp.end(), 0);
        map<vector<int>, long long> deg_count;
        long long total = brute(n, comp, n, &deg_count);
        assert(mint(total) == count_trees(n));
        long long sum = 0;
        for (auto& [d, c] : deg_count) {
            assert(mint(c) == count_with_degrees(d));
            sum += c;
        }
        assert(sum == total);
        // 頂点 0 の次数が j の木は C(n-2, j-1) (n-1)^(n-1-j) 個
        if (n >= 2) {
            for (int j = 1; j <= n - 1; j++) {
                long long c = 0;
                for (auto& [d, cnt] : deg_count)
                    if (d[0] == j) c += cnt;
                mint expect = fact[n - 2] * ifact[j - 1] * ifact[n - 1 - j] * mint(n - 1).pow(n - 1 - j);
                assert(mint(c) == expect);
            }
        }
    }
    // 成分の大きさの列（連続する番号を 1 つの成分にする）をすべて試す
    for (int n = 1; n <= 7; n++) {
        for (int mask = 0; mask < (1 << (n - 1)); mask++) {
            vector<int> comp(n), s(1, 1);
            for (int i = 1; i < n; i++) {
                if (mask >> (i - 1) & 1) {
                    comp[i] = comp[i - 1] + 1;
                    s.push_back(1);
                } else {
                    comp[i] = comp[i - 1];
                    s.back()++;
                }
            }
            int k = s.size();
            assert(mint(brute(n, comp, k, nullptr)) == connect_components(s));
        }
    }
}

int main() {
    init();
    self_check();
    int n;
    cin >> n;
    vector<int> d(n);
    for (int& x : d) cin >> x;
    cout << count_trees(n).val() << ' ' << count_with_degrees(d).val() << '\n';
}
