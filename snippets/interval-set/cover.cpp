// 覆われた区間の集合（互いに重ならず、隣り合わない [l, r) を左端 → 右端の map で持つ）
// 入力：Q、続く Q 行は「1 l r」（[l, r) を覆う）・「2 l r」（[l, r) の覆いを外す）・
//       「3 x」（x を含む区間を「l r」で、なければ -1 を出力）・「4」（覆われた長さの合計と区間の数）・
//       「5 x」（x 以上で覆われていない最小の値）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct IntervalSet {
    const long long INF = 1LL << 62;
    map<long long, long long> mp{{-INF, -INF}, {INF, INF}};  // 左端 → 右端。両端は長さ 0 の番兵
    long long total = 0;                                      // 覆われた長さの合計

    // x を含む区間。なければ end()
    map<long long, long long>::iterator find(long long x) {
        auto it = prev(mp.upper_bound(x));
        return x < it->second ? it : mp.end();
    }
    // [l, r) を覆う。重なる・接する区間は 1 つにまとめる
    void insert(long long l, long long r) {
        if (l >= r) return;
        auto it = mp.upper_bound(l);
        if (l <= prev(it)->second) --it;  // 左の区間と重なるか接する
        while (it->first <= r) {          // 右の番兵で必ず止まる
            l = min(l, it->first);
            r = max(r, it->second);
            total -= it->second - it->first;
            it = mp.erase(it);
        }
        mp[l] = r;
        total += r - l;
    }
    // [l, r) の覆いを外す。はみ出した部分は残す
    void erase(long long l, long long r) {
        if (l >= r) return;
        auto it = mp.upper_bound(l);
        if (l < prev(it)->second) --it;
        while (it->first < r) {
            auto [a, b] = *it;
            total -= b - a;
            it = mp.erase(it);
            if (a < l) { mp[a] = l; total += l - a; }
            if (r < b) { mp[r] = b; total += b - r; }
        }
    }
    // x 以上で覆われていない最小の値
    long long next_free(long long x) {
        auto it = find(x);
        return it == mp.end() ? x : it->second;
    }
};
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    IntervalSet s;
    const int W = 64;           // 座標が [0, W) のときだけ素朴な配列で確かめる
    vector<bool> naive(W, false);
    bool small = true;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            long long l, r;
            cin >> l >> r;
            if (t == 1) s.insert(l, r); else s.erase(l, r);
            if (l < 0 || r > W) small = false;
            if (small) for (long long j = max(l, 0LL); j < min(r, (long long)W); j++) naive[j] = (t == 1);
        } else if (t == 3) {
            long long x;
            cin >> x;
            auto it = s.find(x);
            if (it == s.mp.end()) cout << -1 << '\n';
            else cout << it->first << ' ' << it->second << '\n';
        } else if (t == 4) {
            cout << s.total << ' ' << s.mp.size() - 2 << '\n';
        } else {
            long long x;
            cin >> x;
            cout << s.next_free(x) << '\n';
        }
        if (small) {
            // 素朴な配列と、区間が重ならず隣り合わないことを確かめる
            long long sum = 0;
            for (int j = 0; j < W; j++) sum += naive[j];
            assert(sum == s.total);
            for (auto it = next(s.mp.begin()); next(it) != s.mp.end(); ++it) {
                assert(it->first < it->second && it->second < next(it)->first);
                for (long long j = it->first; j < it->second; j++) assert(naive[j]);
            }
        }
    }
}
