// 小さい順に K 個を列挙する：昇順の a（長さ n）と b（長さ m）から 1 つずつ選んだ和 a[i] + b[j] の
// n * m 個のうち、小さい方から k 個を（同じ値も重複して数えて）出力する。
// 各組 (i, j) の「親」を (i, j - 1)（j = 0 なら (i - 1, 0)）と決め、取り出した組から子だけを入れる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<long long> k_smallest_sums(const vector<long long>& a, const vector<long long>& b, int k) {
    int n = a.size(), m = b.size();
    // (和, i, j) を和の小さい順に取り出す
    using T = tuple<long long, int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    vector<long long> res;
    if (n == 0 || m == 0) return res;
    pq.push({a[0] + b[0], 0, 0});  // 根：最小の和
    while ((int)res.size() < k && !pq.empty()) {
        auto [s, i, j] = pq.top();
        pq.pop();
        res.push_back(s);
        // 子は親以上の和を持つ（a・b が昇順なので）。各組の親は 1 つなので、同じ組は 2 回入らない
        if (j + 1 < m) pq.push({a[i] + b[j + 1], i, j + 1});
        if (j == 0 && i + 1 < n) pq.push({a[i + 1] + b[0], i + 1, 0});
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    assert(is_sorted(a.begin(), a.end()) && is_sorted(b.begin(), b.end()));
    assert(0 <= k && (long long)k <= (long long)n * m);
    vector<long long> res = k_smallest_sums(a, b, k);
    // 全部を並べた結果と照らし合わせる（確かめるためだけ）
    vector<long long> all;
    for (long long x : a) for (long long y : b) all.push_back(x + y);
    sort(all.begin(), all.end());
    assert(equal(res.begin(), res.end(), all.begin()));
    for (int t = 0; t < (int)res.size(); t++) cout << res[t] << (t + 1 < (int)res.size() ? " " : "");
    cout << '\n';
}
