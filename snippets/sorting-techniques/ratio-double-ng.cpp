// 失敗例（本文には取り込まない）：比率を double で比べると、差が 10^-18 程度の 2 つの率が
// 同じ値に丸められ、同点として番号順に並んでしまう。正しい出力は "2 1"。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<double> r(n);
    for (int i = 0; i < n; i++) r[i] = (double)a[i] / (a[i] + b[i]);
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&](int i, int j) { return r[i] > r[j]; });
    for (int k = 0; k < n; k++) cout << idx[k] + 1 << (k + 1 < n ? ' ' : '\n');
}
