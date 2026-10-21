#include <bits/stdc++.h>
using namespace std;

// 1 ≤ a_1 ≤ … ≤ a_k ≤ n の列（広義単調）を、b_i = a_i + i（0-indexed の i）で
// 1 ≤ b_1 < … < b_k ≤ n + k − 1 の列（狭義単調 = k 元部分集合）に移す対応を、
// 小さい n・k で全列挙して確かめる。

// 本文の条件 1・2 で使う、X・Y の条件をそのまま書いた判定
bool in_X(const vector<int>& a, int n) {  // 広義単調で 1 以上 n 以下か
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] < 1 || a[i] > n) return false;
        if (i > 0 && a[i - 1] > a[i]) return false;
    }
    return true;
}
bool in_Y(const vector<int>& b, int n) {  // 狭義単調で 1 以上 n + k − 1 以下か
    int k = b.size();
    for (int i = 0; i < k; i++) {
        if (b[i] < 1 || b[i] > n + k - 1) return false;
        if (i > 0 && b[i - 1] >= b[i]) return false;
    }
    return true;
}
// --8<-- [start:core]
vector<int> f(const vector<int>& a) {  // 元の対象 → 言い換えた対象
    vector<int> b(a.size());
    for (int i = 0; i < (int)a.size(); i++) b[i] = a[i] + i;
    return b;
}
vector<int> g(const vector<int>& b) {  // 逆向きの写像
    vector<int> a(b.size());
    for (int i = 0; i < (int)b.size(); i++) a[i] = b[i] - i;
    return a;
}
// X の全要素 xs と Y の全要素 ys について、全単射かを確かめる
void check_bijection(const vector<vector<int>>& xs, const vector<vector<int>>& ys, int n) {
    set<vector<int>> image;
    for (auto& a : xs) {
        auto b = f(a);
        assert(in_Y(b, n));  // 1. 行き先が Y に入る
        assert(g(b) == a);   // 3. 行って戻ると元に戻る（単射）
        image.insert(b);
    }
    for (auto& b : ys) {
        assert(in_X(g(b), n));  // 2. 逆向きの行き先が X に入る
        assert(f(g(b)) == b);   // 3. 戻って行くと元に戻る（全射）
    }
    assert(image.size() == ys.size());
}
// --8<-- [end:core]

// 長さ k、各値 1..m の列をすべて作り、条件 ok を満たすものを返す
template <class F>
vector<vector<int>> enumerate(int k, int m, F ok) {
    vector<vector<int>> res;
    vector<int> cur(k);
    auto dfs = [&](auto&& self, int i) -> void {
        if (i == k) {
            if (ok(cur)) res.push_back(cur);
            return;
        }
        for (int v = 1; v <= m; v++) {
            cur[i] = v;
            self(self, i + 1);
        }
    };
    dfs(dfs, 0);
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    auto xs = enumerate(k, n, [&](const vector<int>& a) { return in_X(a, n); });
    auto ys = enumerate(k, n + k - 1, [&](const vector<int>& b) { return in_Y(b, n); });
    check_bijection(xs, ys, n);
    cout << xs.size() << ' ' << ys.size() << '\n';
}
