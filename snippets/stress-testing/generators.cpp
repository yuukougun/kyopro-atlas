#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng;

long long rand_int(long long l, long long r) {  // 閉区間 [l, r] の整数
    return uniform_int_distribution<long long>(l, r)(rng);
}

// --8<-- [start:distinct]
// 1 以上 m 以下から互いに異なる n 個（n ≤ m）を選んで並べる
vector<long long> distinct_values(int n, long long m) {
    set<long long> used;
    vector<long long> a;
    while ((int)a.size() < n) {
        long long x = rand_int(1, m);
        if (used.insert(x).second) a.push_back(x);  // 既に出た値は捨てる
    }
    return a;
}
// --8<-- [end:distinct]

// --8<-- [start:tree]
// n 頂点の木の辺。頂点 i（1 ≤ i < n）を i より前の頂点につなぎ、番号をかき混ぜる
vector<pair<int, int>> random_tree(int n) {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int p = rand_int(0, i - 1);
        edges.push_back({perm[p], perm[i]});
    }
    shuffle(edges.begin(), edges.end(), rng);
    return edges;
}

// パス状の木は上の作り方ではめったに出ないので、別に作る
vector<pair<int, int>> random_path(int n) {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) edges.push_back({perm[i - 1], perm[i]});
    return edges;
}
// --8<-- [end:tree]

// 木であること（n - 1 本の辺で連結）を確かめる
bool is_tree(int n, const vector<pair<int, int>>& edges) {
    if ((int)edges.size() != n - 1) return false;
    vector<int> root(n);
    iota(root.begin(), root.end(), 0);
    auto leader = [&](auto&& self, int v) -> int { return root[v] == v ? v : root[v] = self(self, root[v]); };
    for (auto [u, v] : edges) {
        int ru = leader(leader, u), rv = leader(leader, v);
        if (ru == rv) return false;  // 閉路ができる
        root[ru] = rv;
    }
    return true;
}

int main() {
    int trials;
    unsigned long long seed;
    cin >> trials >> seed;
    rng.seed(seed);
    for (int t = 0; t < trials; t++) {
        int n = rand_int(1, 8);
        vector<long long> a = distinct_values(n, 10);
        assert(set<long long>(a.begin(), a.end()).size() == a.size());
        for (long long x : a) assert(1 <= x && x <= 10);
        assert(is_tree(n, random_tree(n)));
        assert(is_tree(n, random_path(n)));
    }
    cout << "ok\n";
}
