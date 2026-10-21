#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 過半数（N/2 を超える個数）を占める値を返す。なければ nullopt
optional<int> majority(const vector<int>& a) {
    int cand = 0, cnt = 0;
    for (int x : a) {
        if (cnt == 0) cand = x, cnt = 1;    // 残りがなければ x を新しい候補にする
        else if (x == cand) cnt++;          // 同じ値なら積む
        else cnt--;                         // 違う値なら 1 組打ち消す
    }
    // 候補は「過半数があればこれ」というだけなので、数え直して確かめる
    long long c = count(a.begin(), a.end(), cand);
    if (2 * c > (long long)a.size()) return cand;
    return nullopt;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto r = majority(a);
    // 素朴な数え方と比べる
    map<int, int> freq;
    for (int x : a) freq[x]++;
    optional<int> naive;
    for (auto [v, c] : freq)
        if (2 * c > n) naive = v;
    assert(r == naive);
    if (r) cout << *r << '\n';
    else cout << -1 << '\n';
}
