#include <bits/stdc++.h>
using namespace std;

// 立方体の面 0..5（上・下・前・後・左・右）の回転を、2 つの 90 度回転から生成して確かめる
int main() {
    vector<int> id = {0, 1, 2, 3, 4, 5};
    vector<int> r1 = {0, 1, 5, 4, 2, 3};  // 上下を通る軸：前→右→後→左→前
    vector<int> r2 = {5, 4, 2, 3, 0, 1};  // 前後を通る軸：上→右→下→左→上
    auto compose = [](const vector<int>& p, const vector<int>& q) {
        vector<int> r(6);
        for (int i = 0; i < 6; i++) r[i] = q[p[i]];
        return r;
    };
    set<vector<int>> group = {id};
    queue<vector<int>> que;
    que.push(id);
    while (!que.empty()) {
        auto p = que.front();
        que.pop();
        for (auto& g : {r1, r2}) {
            auto q = compose(p, g);
            if (group.insert(q).second) que.push(q);
        }
    }
    assert(group.size() == 24);

    // 巡回の長さの型ごとに数える
    map<vector<int>, int> types;
    for (auto& p : group) {
        vector<int> seen(6, 0), lens;
        for (int i = 0; i < 6; i++) {
            if (seen[i]) continue;
            int len = 0;
            for (int v = i; !seen[v]; v = p[v]) { seen[v] = 1; len++; }
            lens.push_back(len);
        }
        sort(lens.begin(), lens.end());
        types[lens]++;
    }
    for (auto& [lens, c] : types) {
        for (int x : lens) cout << x;
        cout << ' ' << c << '\n';
    }

    // k 色の面の塗り方：Burnside の式と全列挙を比べる
    int k;
    cin >> k;
    long long sum = 0;
    for (auto& p : group) {
        vector<int> seen(6, 0);
        int cycles = 0;
        for (int i = 0; i < 6; i++) {
            if (seen[i]) continue;
            cycles++;
            for (int v = i; !seen[v]; v = p[v]) seen[v] = 1;
        }
        long long fix = 1;
        for (int j = 0; j < cycles; j++) fix *= k;  // 巡回ごとに 1 色
        sum += fix;
    }
    set<vector<int>> classes;
    int total = 1;
    for (int i = 0; i < 6; i++) total *= k;
    for (int code = 0; code < total; code++) {
        vector<int> a(6);
        int c = code;
        for (int i = 0; i < 6; i++) { a[i] = c % k; c /= k; }
        vector<int> best = a;
        for (auto& p : group) {
            vector<int> b(6);
            for (int i = 0; i < 6; i++) b[p[i]] = a[i];
            best = min(best, b);
        }
        classes.insert(best);
    }
    assert(sum % 24 == 0 && sum / 24 == (long long)classes.size());
    cout << sum / 24 << '\n';
}
