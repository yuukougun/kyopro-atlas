// 値つきの区間の集合（座標の全体を区間に区切り、各区間に値を持つ）
// 入力：N Q、続く Q 行は「1 l r c」（[l, r) を色 c に塗る）・「2 x」（x の色を出力）・「3 c」（色 c のマスの数を出力）
// 最初は [0, N) のすべてが色 0。N は 10^9 まででよい
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct IntervalMap {
    map<long long, long long> mp;  // 左端 → 値。区間は [左端, 次の左端)

    // [lo, hi) の全体を値 v0 にする。hi は右の番兵で、値は使わない
    IntervalMap(long long lo, long long hi, long long v0) {
        mp[lo] = v0;
        mp[hi] = LLONG_MIN;
    }
    // x を含む区間（lo <= x < hi）。upper_bound の 1 つ前
    map<long long, long long>::iterator find(long long x) {
        return prev(mp.upper_bound(x));
    }
    // x を左端とする区間を作って返す。x が区間の途中なら 2 つに分ける
    map<long long, long long>::iterator split(long long x) {
        auto it = find(x);
        if (it->first == x) return it;
        return mp.emplace_hint(next(it), x, it->second);
    }
    // [l, r) を値 v にする。消える区間ごとに f(左端, 右端, 値) を呼ぶ
    template <class F>
    void assign(long long l, long long r, long long v, F f) {
        if (l >= r) return;
        auto itl = split(l);
        auto itr = split(r);
        for (auto it = itl; it != itr; ++it) f(it->first, next(it)->first, it->second);
        mp.erase(itl, itr);
        mp[l] = v;
    }
};
// --8<-- [end:core]

int main() {
    long long n;
    int q;
    cin >> n >> q;
    IntervalMap im(0, n, 0);
    map<long long, long long> cnt;  // 色 → マスの数
    cnt[0] = n;
    vector<long long> naive;  // N が小さいときだけ素朴な配列で確かめる
    if (n <= 1000) naive.assign(n, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            long long l, r, c;
            cin >> l >> r >> c;
            im.assign(l, r, c, [&](long long a, long long b, long long v) { cnt[v] -= b - a; });
            if (l < r) cnt[c] += r - l;
            if (n <= 1000) for (long long j = l; j < r; j++) naive[j] = c;
        } else if (t == 2) {
            long long x;
            cin >> x;
            long long c = im.find(x)->second;
            if (n <= 1000) assert(c == naive[x]);
            cout << c << '\n';
        } else {
            long long c;
            cin >> c;
            if (n <= 1000) assert(cnt[c] == count(naive.begin(), naive.end(), c));
            cout << cnt[c] << '\n';
        }
        // 区間の数は 1 回の塗りで高々 2 つしか増えない
        assert((int)im.mp.size() <= 2 + 2 * (i + 1));
    }
}
