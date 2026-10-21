// 足場 0, 1, …, n-1 を 1 つ先か 2 つ先へ跳んで進み、跳ぶたびに高さの差のコストがかかる。
// 足場 n-1 までのコストの和の最小を、貰う形と配る形の両方で求めて一致を確かめる。
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;  // 到達できない印。コストを足してもあふれない大きさ

long long solve_pull(const vector<long long>& h) {
    int n = h.size();
    // --8<-- [start:pull]
    // dp[i] ＝ 足場 i に着くまでのコストの和の最小
    vector<long long> dp(n, INF);
    dp[0] = 0;  // 出発点はコスト 0
    for (int i = 1; i < n; i++) {
        // 貰う：dp[i] を、遷移元 i-1 と i-2 から集める
        dp[i] = min(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    // --8<-- [end:pull]
    return dp[n - 1];
}

long long solve_push(const vector<long long>& h) {
    int n = h.size();
    // --8<-- [start:push]
    vector<long long> dp(n, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == INF) continue;  // 到達できない状態からは配らない
        // 配る：確定した dp[i] を、遷移先 i+1 と i+2 へ送る
        for (int j = i + 1; j <= i + 2 && j < n; j++) {
            dp[j] = min(dp[j], dp[i] + abs(h[j] - h[i]));
        }
    }
    // --8<-- [end:push]
    return dp[n - 1];
}

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    long long a = solve_pull(h), b = solve_push(h);
    assert(a == b);  // どちらの形でも各遷移を 1 回ずつ使うので同じ値になる
    cout << a << '\n';
}
