// 置換の偶奇：巡回の個数から置換の符号（swap の回数の偶奇）を求め、
// 3 要素の巡回だけで列 a を列 b に変えられるかを判定する。
// 入力：n、列 a、列 b。出力：Yes / No。
// 自己検査：小さい n で、巡回の個数による偶奇と転倒数の偶奇が一致すること、
// 判定の結果が 3 要素の巡回による全探索と一致することを確かめる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// p は 0, 1, ..., n-1 の並べ替え。swap の回数の偶奇（0 なら偶置換、1 なら奇置換）を返す
int perm_parity(const vector<int>& p) {
    int n = p.size();
    int cycles = 0;
    vector<bool> seen(n, false);
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        cycles++;  // s から始まる新しい巡回
        for (int v = s; !seen[v]; v = p[v]) seen[v] = true;
    }
    return (n - cycles) % 2;  // 最小の swap 回数 n − c の偶奇
}
// --8<-- [end:core]

// --8<-- [start:judge]
// 任意の 3 か所を巡回させる操作だけで、a を b に変えられるか
bool reachable_by_3cycles(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size();
    vector<long long> sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    if (sa != sb) return false;                  // 値の多重集合が違えば無理
    for (int i = 0; i + 1 < n; i++) {
        if (sa[i] == sa[i + 1]) return true;     // 同じ値があれば偶奇を調整できる
    }
    // 値がすべて異なる：a[i] が b の中で何番目にあるかを p[i] とする
    vector<int> idx_b(n);
    iota(idx_b.begin(), idx_b.end(), 0);
    sort(idx_b.begin(), idx_b.end(), [&](int i, int j) { return b[i] < b[j]; });
    vector<int> idx_a(n);
    iota(idx_a.begin(), idx_a.end(), 0);
    sort(idx_a.begin(), idx_a.end(), [&](int i, int j) { return a[i] < a[j]; });
    vector<int> p(n);
    for (int k = 0; k < n; k++) p[idx_a[k]] = idx_b[k];  // k 番目に小さい値の行き先
    return perm_parity(p) == 0;                  // 偶置換なら作れる
}
// --8<-- [end:judge]

// 転倒数の偶奇（O(n^2)。検査用）
int inversion_parity(const vector<int>& p) {
    int n = p.size(), inv = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i] > p[j]) inv ^= 1;
    return inv;
}

// 3 要素の巡回で a から b に届くかの全探索（検査用。n は小さい）
bool brute(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size();
    set<vector<long long>> seen{a};
    queue<vector<long long>> q;
    q.push(a);
    while (!q.empty()) {
        vector<long long> v = q.front();
        q.pop();
        if (v == b) return true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    if (i == j || j == k || i == k) continue;
                    vector<long long> w = v;
                    w[i] = v[k];  // i ← k ← j ← i の向きに 1 つずつ動かす
                    w[j] = v[i];
                    w[k] = v[j];
                    if (seen.insert(w).second) q.push(w);
                }
    }
    return false;
}

int main() {
    // 自己検査 1：n ≤ 6 のすべての順列で、2 つの偶奇の求め方が一致する
    for (int n = 0; n <= 6; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            assert(perm_parity(p) == inversion_parity(p));
        } while (next_permutation(p.begin(), p.end()));
    }
    // 自己検査 2：n ≤ 5 で、判定が全探索と一致する。
    // 値が 0〜2 の列（重複が多い）と、値がすべて異なる列を交互に試す
    mt19937 rng(12345);
    for (int iter = 0; iter < 600; iter++) {
        int n = rng() % 6;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) a[i] = (iter % 2 == 0) ? (long long)(rng() % 3) : i * 7 + 3;
        b = a;
        shuffle(b.begin(), b.end(), rng);
        if (rng() % 4 == 0 && n > 0) b[0] = rng() % 3;  // 多重集合が違う場合も混ぜる
        assert(reachable_by_3cycles(a, b) == brute(a, b));
    }

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    cout << (reachable_by_3cycles(a, b) ? "Yes" : "No") << '\n';
}
