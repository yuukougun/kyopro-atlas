// 増分が単調なら 1 単位ずつ貪欲に配る：x_0 + … + x_{n−1} = K（x_i ≥ 0）のもとで Σ a_i x_i^2 を最小化する。
// a_i x^2 は下に凸で、1 増やすときの増分 a_i (2x + 1) は x について増える。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    vector<long long> x(n, 0);
    // (次に 1 増やすときの増分, 添字) の小さい順に取り出す
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    for (int i = 0; i < n; i++) pq.push({a[i] * (2 * x[i] + 1), i});
    long long cost = 0;
    for (long long t = 0; t < k; t++) {
        auto [d, i] = pq.top();
        pq.pop();
        cost += d;  // 増分の小さいところへ 1 単位配る
        x[i]++;
        pq.push({a[i] * (2 * x[i] + 1), i});  // 次の増分は前より大きい
    }
    cout << cost << '\n';
    // --8<-- [end:core]
}
