// CI の確認用：gnu++23 の機能（views::enumerate・println）と同梱の ACL v1.6 が使えることを確かめる
#include <bits/stdc++.h>
#include <atcoder/dsu>
#include <atcoder/modint>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    atcoder::dsu d(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d.merge(a, b);
    }
    vector<int> sizes;
    for (const auto& [i, g] : d.groups() | views::enumerate) sizes.push_back(ssize(g));
    ranges::sort(sizes);
    atcoder::modint998244353 x = 3, y = 5;
    println("{} {}", sizes.size(), (x - y).val());  // v1.6 では val() は int
}
