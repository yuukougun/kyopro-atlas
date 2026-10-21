#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

// 区間 [l, r) に含まれる値の種類数を、クエリを右端の順に並べ替えて答える
vector<int> distinct_count(const vector<long long>& a, const vector<pair<int, int>>& qs) {
    int n = a.size(), q = qs.size();
    // 値を 0..K-1 に座標圧縮する（last を配列で持つため）
    vector<long long> xs = a;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    vector<int> c(n);
    for (int i = 0; i < n; i++) c[i] = lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();

    // --8<-- [start:core]
    vector<int> ord(q);                       // クエリの番号を右端の順に並べる
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return qs[i].second < qs[j].second; });

    atcoder::fenwick_tree<int> bit(n);        // 各値の最後の出現位置にだけ 1
    vector<int> last(xs.size(), -1);          // 値ごとの最後の出現位置（なければ -1）
    vector<int> ans(q);
    int r = 0;                                // [0, r) まで BIT に反映済み
    for (int k : ord) {
        auto [l, qr] = qs[k];
        while (r < qr) {                      // 右端を qr まで伸ばす
            if (last[c[r]] != -1) bit.add(last[c[r]], -1);  // 古い位置の 1 を消す
            bit.add(r, 1);
            last[c[r]] = r;
            r++;
        }
        ans[k] = bit.sum(l, qr);              // 元の番号 k の場所に書く
    }
    // --8<-- [end:core]
    return ans;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<pair<int, int>> qs(q);
    for (auto& [l, r] : qs) {
        cin >> l >> r;  // 入力は 1-indexed の閉区間 [l, r]
        l--;            // 0-indexed の半開区間 [l - 1, r) にする
    }
    vector<int> ans = distinct_count(a, qs);
    // 素朴な方法と照らし合わせる
    for (int k = 0; k < q; k++) {
        set<long long> s(a.begin() + qs[k].first, a.begin() + qs[k].second);
        assert(ans[k] == (int)s.size());
    }
    for (int x : ans) cout << x << '\n';
}
