// 締め切りのある仕事：仕事 i は、行った日の a[i] 日後に報酬 b[i] を受け取る。
// 1 日に 1 件まで行えるとき、m 日後（日 0, 1, …, m-1 に行い、m 日目まで）に受け取れる報酬の合計の最大。
// 後ろの日から決め、その日に間に合う仕事の中で報酬が最大のものを選ぶ。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long max_reward(int m, const vector<pair<int, int>>& jobs) {
    // by_a[k]：a = k の仕事の報酬（k > m の仕事はどの日にも間に合わない）
    vector<vector<int>> by_a(m + 1);
    for (auto [a, b] : jobs) {
        if (a <= m) by_a[a].push_back(b);
    }
    priority_queue<int> pq;  // 使えるようになった仕事の報酬（大きい順に取り出す）
    long long total = 0;
    for (int d = m - 1; d >= 0; d--) {
        // 日 d に行うと日 d + a に受け取る。d + a <= m、すなわち a = m - d の仕事が新しく使える
        for (int b : by_a[m - d]) pq.push(b);
        if (!pq.empty()) {  // 空なら、この日は何もしない
            total += pq.top();
            pq.pop();
        }
    }
    return total;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> jobs(n);
    for (auto& [a, b] : jobs) cin >> a >> b;
    for (auto [a, b] : jobs) assert(a >= 1 && b >= 0);
    cout << max_reward(m, jobs) << '\n';
}
