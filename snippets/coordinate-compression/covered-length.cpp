// 区間と座標圧縮：N 個の半開区間 [l, r) のどれかに覆われる部分の長さの合計を求める。
// 両端点 l と r を圧縮し、隣り合う番号の間（基本区間）ごとにいもす法で重なりを数える。
// 長さは圧縮後の番号ではなく、元の座標 vals[j + 1] - vals[j] で測る。
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
    vector<long long> vals;
    for (int i = 0; i < n; i++) {
        vals.push_back(l[i]);  // 左端も
        vals.push_back(r[i]);  // 右端も入れる（閉区間 [l, r] なら r + 1 を入れる）
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int k = vals.size();
    auto idx = [&](long long x) { return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()); };

    vector<int> diff(k + 1, 0);  // 番号 j は基本区間 [vals[j], vals[j + 1]) を表す
    for (int i = 0; i < n; i++) {
        diff[idx(l[i])]++;
        diff[idx(r[i])]--;
    }
    long long total = 0;
    int cnt = 0;
    for (int j = 0; j + 1 < k; j++) {
        cnt += diff[j];                          // 基本区間 j を覆う区間の数
        if (cnt > 0) total += vals[j + 1] - vals[j];  // 長さは元の座標で測る
    }
    cout << total << '\n';
    // --8<-- [end:core]

    // 座標が小さいときは、覆われる整数の個数を素朴に数えて比べる
    bool small = true;
    for (int i = 0; i < n; i++) small = small && -1000 <= l[i] && r[i] <= 1000;
    if (small) {
        long long naive = 0;
        for (long long x = -1000; x < 1000; x++) {
            bool covered = false;
            for (int i = 0; i < n; i++) covered = covered || (l[i] <= x && x < r[i]);
            if (covered) naive++;
        }
        assert(naive == total);
    }
}
