#include <bits/stdc++.h>
using namespace std;

// 隣り合う 2 項の差の絶対値がすべて異なるか
bool is_valid(const vector<int>& p) {
    int n = p.size();
    vector<bool> used(n, false);
    for (int i = 0; i + 1 < n; i++) {
        int d = abs(p[i] - p[i + 1]);
        if (used[d]) return false;
        used[d] = true;
    }
    return true;
}

// --8<-- [start:core]
// 小さい n で、条件を満たす順列を辞書順で最初に見つかるものだけ求める
vector<int> brute(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    do {
        if (is_valid(p)) return p;
    } while (next_permutation(p.begin(), p.end()));
    return {};  // 存在しない
}

// 実験の結果から予想した構築：1, n, 2, n - 1, 3, … と両端から交互に取る
vector<int> zigzag(int n) {
    vector<int> p;
    int l = 1, r = n;
    while (l <= r) {
        p.push_back(l++);
        if (l <= r) p.push_back(r--);
    }
    return p;
}
// --8<-- [end:core]

int main() {
    int m;
    cin >> m;
    for (int n = 1; n <= m; n++) {
        vector<int> p = brute(n);
        assert(!p.empty());
        assert(p == zigzag(n));  // 実験の結果と予想が一致する
        for (int i = 0; i < n; i++) cout << p[i] << (i + 1 < n ? ' ' : '\n');
    }
    for (int n = 1; n <= 3000; n++) assert(is_valid(zigzag(n)));  // 大きい n でも確かめる
}
