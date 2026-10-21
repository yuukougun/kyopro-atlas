// 接頭辞ごとの K 番目に大きい値：大きさ K の最小ヒープに「今までの上位 K 個」を保つ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= k && k <= n);

    // --8<-- [start:core]
    priority_queue<long long, vector<long long>, greater<long long>> q;  // 上位 K 個（top が最小）
    for (int i = 0; i < n; i++) {
        q.push(a[i]);
        if ((int)q.size() > k) q.pop();  // K + 1 個になったら最小を捨てる
        if ((int)q.size() == k) cout << q.top() << '\n';  // a[0..i] の K 番目に大きい値
    }
    // --8<-- [end:core]
}
