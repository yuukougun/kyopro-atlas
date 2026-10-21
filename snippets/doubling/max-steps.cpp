#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long S;
    cin >> n >> S;
    vector<int> f(n);
    vector<long long> w(n);  // 1 ≤ w[v] ≤ 10^9
    for (int v = 0; v < n; v++) cin >> f[v];
    for (int v = 0; v < n; v++) cin >> w[v];

    // --8<-- [start:core]
    const int LOG = 60;  // 答えは S ≤ 10^18 以下なので 2^60 未満
    const long long INF = 2'000'000'000'000'000'000LL;  // S より大きい。和をここで頭打ちにする
    vector<vector<int>> nxt(LOG, vector<int>(n));
    vector<vector<long long>> sum(LOG, vector<long long>(n));  // 半開：時刻 [0, 2^k) の和
    nxt[0] = f;
    sum[0] = w;
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) {
            int mid = nxt[k][v];
            nxt[k + 1][v] = nxt[k][mid];
            sum[k + 1][v] = min(INF, sum[k][v] + sum[k][mid]);  // 2 × INF でも long long に収まる
        }
    }
    // 0 から進み、通った状態の w の和が S 以下に収まる最大の回数 t
    int v = 0;
    long long t = 0, used = 0;
    for (int k = LOG - 1; k >= 0; k--) {  // 上の段から
        if (used + sum[k][v] <= S) {      // 2^k 回跳んでも条件を満たすなら跳ぶ
            used += sum[k][v];
            t += 1LL << k;
            v = nxt[k][v];
        }
    }
    // --8<-- [end:core]

    {  // 素朴なシミュレーションと比べる（答えが小さいときだけ）
        if (t <= 100000) {
            int u = 0;
            long long s = 0, cnt = 0;
            while (s + w[u] <= S) {
                s += w[u];
                u = f[u];
                cnt++;
            }
            assert(cnt == t);
        }
    }
    cout << t << '\n';
}
