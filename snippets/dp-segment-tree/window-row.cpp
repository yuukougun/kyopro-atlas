// 前の段の窓の最大を取る DP：N 種類の材料を、それぞれ使わないか L_i 以上 R_i 以下の量だけ使う（価値 V_i）。
// 合計の量をちょうど W にするときの価値の和の最大を求める。
// 段ごとに、遷移元の窓 [j − R_i, j − L_i] が j とともに右へ動くので、単調 deque（スライド最大値）で取る。
// 入力：W N、続く N 行に L_i R_i V_i（1 ≤ L_i ≤ R_i）。出力：価値の和の最大（作れなければ -1）
#include <bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 62);  // 作れない量（−∞）

// --8<-- [start:core]
// prev から次の段を作る：nxt[j] = max(prev[j], max_{j−r ≤ k ≤ j−l} prev[k] + v)
vector<long long> next_row(const vector<long long>& prev, int l, int r, long long v) {
    int w = prev.size() - 1;
    vector<long long> nxt = prev;  // 材料を使わない
    deque<int> dq;                 // 添字を入れる。先頭から末尾へ prev の値は狭義減少
    for (int j = 0; j <= w; j++) {
        int k = j - l;             // 窓の右端が k に進んだので、k を入れる
        if (k >= 0 && prev[k] != NEG) {  // 作れない量は入れない
            while (!dq.empty() && prev[dq.back()] <= prev[k]) dq.pop_back();
            dq.push_back(k);
        }
        while (!dq.empty() && dq.front() < j - r) dq.pop_front();  // 窓の左端 j − r より前は捨てる
        if (!dq.empty()) nxt[j] = max(nxt[j], prev[dq.front()] + v);
    }
    return nxt;
}
// --8<-- [end:core]

int main() {
    int w, n;
    cin >> w >> n;
    vector<long long> dp(w + 1, NEG);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        assert(1 <= l && l <= r);
        vector<long long> nxt = next_row(dp, l, r, v);
        // 素朴に窓を全部見る O(W (R − L)) の遷移で確かめる
        for (int j = 0; j <= w; j++) {
            long long want = dp[j];
            for (int k = max(0, j - r); k <= j - l; k++)
                if (dp[k] != NEG) want = max(want, dp[k] + v);
            assert(nxt[j] == want);
        }
        dp = nxt;
    }
    cout << (dp[w] == NEG ? -1 : dp[w]) << '\n';
}
