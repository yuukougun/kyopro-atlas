// ブロックの積み上げ：重さ w[i]・丈夫さ s[i]・価値 v[i] のブロックをいくつか選んで積み、
// どのブロックも「上に載る重さの合計 ≤ 自分の丈夫さ」を満たすときの価値の和の最大。
// s + w の小さい順（上から下への順）に並べ、新しいブロックを一番下に足すナップサックにする。
// n が小さければ、選び方と積む順をすべて試す素朴な方法と突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> w(n), s(n);
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> s[i] >> v[i];
    for (int i = 0; i < n; i++) assert(1 <= w[i] && 0 <= s[i] && 0 <= v[i]);

    // --8<-- [start:core]
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    // 上に置く方が先：s + w の小さい順（整数なので割り算も誤差もない）
    sort(ord.begin(), ord.end(), [&](int i, int j) { return s[i] + w[i] < s[j] + w[j]; });

    int maxs = 0, maxw = 0;
    for (int i = 0; i < n; i++) maxs = max(maxs, s[i]), maxw = max(maxw, w[i]);
    const long long NEG = LLONG_MIN / 2;
    // dp[t] ＝ ここまでのブロックから選んで積んだ塔のうち、重さの合計がちょうど t のものの価値の最大
    vector<long long> dp(maxs + maxw + 1, NEG);
    dp[0] = 0;
    for (int i : ord) {
        // 新しいブロックを一番下に置く：上に載る重さは今の合計 t で、t ≤ s[i] が条件
        for (int t = s[i]; t >= 0; t--) {  // 0-1 なので重さの大きい方から
            if (dp[t] == NEG) continue;
            dp[t + w[i]] = max(dp[t + w[i]], dp[t] + v[i]);
        }
    }
    long long ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
    // --8<-- [end:core]

    // 素朴な方法：使うブロックの集合と、上から下への順をすべて試す
    if (n <= 7) {
        long long best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> p;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) p.push_back(i);
            do {
                long long above = 0, val = 0;
                bool ok = true;
                for (int i : p) {  // 上から順に見る
                    if (above > s[i]) ok = false;
                    above += w[i];
                    val += v[i];
                }
                if (ok) best = max(best, val);
            } while (next_permutation(p.begin(), p.end()));
        }
        assert(best == ans);
    }
}
