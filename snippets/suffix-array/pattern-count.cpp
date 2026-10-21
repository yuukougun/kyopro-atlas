// パターン T の出現回数：T を接頭辞に持つ接尾辞は SA 上で連続するので、その範囲を二分探索で求める
// 入力：S、Q、続く Q 行にパターン T。出力：S の中での T の出現回数
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

int main() {
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    vector<int> sa = atcoder::suffix_array(s);
    // --8<-- [start:core]
    // s[sa[i]..) の先頭 |t| 文字と t を比べる（短い接尾辞は途中で切れたまま比べる）
    auto cmp = [&](int i, const string& t) { return s.compare(sa[i], t.size(), t); };
    auto count = [&](const string& t) -> int {
        // lo：先頭 |t| 文字が t 以上になる最初の順位
        int ng = -1, ok = n;
        while (ok - ng > 1) {
            int mid = (ng + ok) / 2;
            if (cmp(mid, t) >= 0) ok = mid;
            else ng = mid;
        }
        int lo = ok;
        // hi：先頭 |t| 文字が t より大きくなる最初の順位
        ng = -1, ok = n;
        while (ok - ng > 1) {
            int mid = (ng + ok) / 2;
            if (cmp(mid, t) > 0) ok = mid;
            else ng = mid;
        }
        int hi = ok;
        return hi - lo;  // sa[lo], …, sa[hi - 1] が t を接頭辞に持つ
    };
    // --8<-- [end:core]

    for (int k = 0; k < q; k++) {
        string t;
        cin >> t;
        int naive = 0;
        for (int p = 0; p + (int)t.size() <= n; p++)
            if (s.compare(p, t.size(), t) == 0) naive++;
        assert(count(t) == naive);
        cout << count(t) << '\n';
    }
}
