#include <bits/stdc++.h>
using namespace std;

long long power(long long b, int e) {  // 0^0 = 1 とする
    long long r = 1;
    for (int i = 0; i < e; i++) r *= b;
    return r;
}

long long binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    long long r = 1;
    for (int i = 0; i < k; i++) r = r * (n - i) / (i + 1);
    return r;
}

int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    // 長さ n、値が 1..m の列をすべて作り、2 つの量ごとに個数を数える（mod は取らない）
    vector<long long> max_cnt(m + 1, 0);   // max_cnt[k]：最大値がちょうど k の列の数
    vector<long long> same_cnt(n, 0);      // same_cnt[j]：隣が同じ値の組がちょうど j 組の列の数
    vector<int> a(n, 1);
    while (true) {
        int mx = *max_element(a.begin(), a.end());
        int same = 0;
        for (int i = 0; i + 1 < n; i++) same += (a[i] == a[i + 1]);
        max_cnt[mx]++;
        same_cnt[same]++;
        int i = 0;  // m 進数のように次の列へ進める
        while (i < n && a[i] == m) a[i++] = 1;
        if (i == n) break;
        a[i]++;
    }
    // 式と照らし合わせる
    for (int k = 1; k <= m; k++) {
        assert(max_cnt[k] == power(k, n) - power(k - 1, n));
    }
    for (int j = 0; j <= n - 1; j++) {
        assert(same_cnt[j] == binom(n - 1, j) * m * power(m - 1, n - 1 - j));
    }
    // --8<-- [end:core]
    for (int k = 1; k <= m; k++) cout << max_cnt[k] << (k == m ? '\n' : ' ');
    for (int j = 0; j <= n - 1; j++) cout << same_cnt[j] << (j == n - 1 ? '\n' : ' ');
    return 0;
}
