#include <bits/stdc++.h>
using namespace std;

int main() {
    long long m;
    cin >> m;
    // --8<-- [start:core]
    // m の部分集合（m の 1 の bit だけからなる数）を、m から 0 まで大きい順に列挙する
    vector<long long> subs;
    for (long long s = m;; s = (s - 1) & m) {
        subs.push_back(s);
        if (s == 0) break;  // 0 を処理してから止める（(0 - 1) & m は m に戻る）
    }
    reverse(subs.begin(), subs.end());  // 昇順にする
    // --8<-- [end:core]
    assert((long long)subs.size() == (1LL << __builtin_popcountll(m)));
    for (int i = 0; i < (int)subs.size(); i++) {
        cout << subs[i] << (i + 1 < (int)subs.size() ? ' ' : '\n');
    }

    // 全体集合の大きさ n の、すべての集合 t とその部分集合 s の組の数は 3^n
    // --8<-- [start:all-pairs]
    int n = 10;
    long long pairs = 0;
    for (int t = 0; t < (1 << n); t++) {
        for (int s = t;; s = (s - 1) & t) {
            pairs++;  // ここで (t, s) の組を処理する
            if (s == 0) break;
        }
    }
    // --8<-- [end:all-pairs]
    assert(pairs == 59049);  // 3^10
}
