// スライド最小値：長さ K のすべての窓 [i - K + 1, i] の最小値を、単調 deque で全体 O(N) で求める
// 入力：N K、A_0 … A_{N-1}（1 ≤ K ≤ N）。出力：N - K + 1 個の最小値
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<long long> sliding_min(const vector<long long>& a, int k) {
    int n = a.size();
    vector<long long> res;
    deque<int> dq;  // 添字を入れる。先頭から末尾へ a の値は狭義増加
    for (int i = 0; i < n; i++) {
        // a[i] 以上の要素は、i より先に窓から出て i より小さくもないので、もう最小にならない
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();  // 窓 [i - k + 1, i] から出た
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> res = sliding_min(a, k);
    assert((int)res.size() == n - k + 1);
    for (int i = 0; i + k <= n; i++) {
        assert(res[i] == *min_element(a.begin() + i, a.begin() + i + k));
        cout << res[i] << (i + k < n ? ' ' : '\n');
    }
}
