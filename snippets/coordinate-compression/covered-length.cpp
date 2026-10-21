// 区間と座標圧縮：N 個の半開区間 [l, r) のどれかに覆われる部分の長さの合計を求める。
// 両端点 l と r を圧縮し、隣り合う番号の間（基本区間）ごとにいもす法で重なりを数える。
// 長さは圧縮後の番号ではなく、元の座標 xs[j + 1] - xs[j] で測る。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        assert(l[i] < r[i]);
    }

    // --8<-- [start:core]
    vector<long long> xs;
    for (int i = 0; i < n; i++) {
        xs.push_back(l[i]);  // 左端も
        xs.push_back(r[i]);  // 右端も入れる（閉区間 [l, r] なら r + 1 を入れる）
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int k = xs.size();
    auto idx = [&](long long x) { return int(lower_bound(xs.begin(), xs.end(), x) - xs.begin()); };

    vector<int> diff(k + 1, 0);  // 番号 j は基本区間 [xs[j], xs[j + 1]) を表す
    for (int i = 0; i < n; i++) {
        diff[idx(l[i])]++;
        diff[idx(r[i])]--;
    }
    long long total = 0;
    int cnt = 0;
    for (int j = 0; j + 1 < k; j++) {
        cnt += diff[j];                          // 基本区間 j を覆う区間の数
        if (cnt > 0) total += xs[j + 1] - xs[j];  // 長さは元の座標で測る
    }
    cout << total << '\n';
    // --8<-- [end:core]
}
