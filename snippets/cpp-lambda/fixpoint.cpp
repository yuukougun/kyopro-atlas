#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:fixpoint]
// ラムダ f を受け取り、f(自分, 引数...) と呼び直す入れ物
template <class F>
struct FixPoint : F {
    explicit FixPoint(F f) : F(std::move(f)) {}
    template <class... Args>
    decltype(auto) operator()(Args&&... args) const {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};
// --8<-- [end:fixpoint]

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(n);  // sz[v]：頂点 0 を根とした v の部分木の頂点数
    // --8<-- [start:core]
    auto dfs = FixPoint([&](auto&& self, int v, int p) -> void {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            self(to, v);  // self は FixPoint。中で自分を足して呼び直してくれる
            sz[v] += sz[to];
        }
    });
    dfs(0, -1);
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << sz[v] << " \n"[v == n - 1];
}
