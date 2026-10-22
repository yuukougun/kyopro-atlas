#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// 各クエリ i について、check(i) が「最初の t 回の操作の後」に true になる最小の t（0 <= t <= m）を返す。
// 一度も true にならなければ m + 1。check(i) は t について単調（false…false true…true）であること。
// reset() は操作 0 回の状態に戻し、apply(j) は j 番目（0-indexed）の操作を行う。
template <class Reset, class Apply, class Check>
vector<int> parallel_binary_search(int q, int m, Reset reset, Apply apply, Check check) {
    vector<int> ng(q, -1), ok(q, m + 1);  // 番兵：t = -1 は不可、t = m + 1 は可とみなす
    while (true) {
        vector<vector<int>> bucket(m + 1);  // bucket[t]：mid = t のクエリ
        bool active = false;
        for (int i = 0; i < q; i++) {
            if (ok[i] - ng[i] > 1) {
                bucket[(ok[i] + ng[i]) / 2].push_back(i);
                active = true;
            }
        }
        if (!active) break;
        reset();
        for (int t = 0; t <= m; t++) {
            if (t > 0) apply(t - 1);  // ここで最初の t 回の操作が済んだ状態になる
            for (int i : bucket[t]) {
                if (check(i)) ok[i] = t;
                else ng[i] = t;
            }
        }
    }
    return ok;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int j = 0; j < m; j++) {
        cin >> a[j] >> b[j];
        a[j]--, b[j]--;
    }
    int q;
    cin >> q;
    vector<int> x(q), y(q);
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
    }

    // --8<-- [start:usage]
    // x[i] と y[i] が初めて連結になるのは、最初の何本の辺を足したときか
    atcoder::dsu d(n);
    auto reset = [&]() { d = atcoder::dsu(n); };       // 1 段ごとに O(N) で作り直す
    auto apply = [&](int j) { d.merge(a[j], b[j]); };
    auto check = [&](int i) { return d.same(x[i], y[i]); };
    vector<int> ans = parallel_binary_search(q, m, reset, apply, check);
    // --8<-- [end:usage]

    // 素朴な方法（クエリごとに辺を先頭から足す）と照らし合わせる
    for (int i = 0; i < q; i++) {
        atcoder::dsu e(n);
        int naive = m + 1;
        for (int t = 0; t <= m; t++) {
            if (t > 0) e.merge(a[t - 1], b[t - 1]);
            if (e.same(x[i], y[i])) {
                naive = t;
                break;
            }
        }
        assert(ans[i] == naive);
    }
    for (int i = 0; i < q; i++) cout << (ans[i] <= m ? ans[i] : -1) << '\n';
}
