// 置換の K 回合成：q[i] = p^K(i)（i から矢印を K 回たどった先）を、
// 各巡回の上で K を巡回の長さで割った余りだけ進めて O(N) で求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    assert(k >= 0);

    // --8<-- [start:core]
    vector<int> q(n);
    vector<bool> seen(n, false);
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        vector<int> cyc;
        for (int v = s; !seen[v]; v = p[v]) {
            seen[v] = true;
            cyc.push_back(v);
        }
        int len = cyc.size();
        int r = k % len;  // K 歩は、長さ len の巡回の上では K mod len 歩と同じ
        for (int j = 0; j < len; j++) q[cyc[j]] = cyc[(j + r) % len];
    }
    // --8<-- [end:core]

    if (k <= 100) {  // 小さい K では素朴に K 回たどった結果と照合する
        for (int i = 0; i < n; i++) {
            int v = i;
            for (long long t = 0; t < k; t++) v = p[v];
            assert(q[i] == v);
        }
    }
    for (int i = 0; i < n; i++) cout << q[i] + 1 << " \n"[i == n - 1];
}
