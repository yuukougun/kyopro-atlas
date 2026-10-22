#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0〜n-1 の順列 p の前に、辞書順で何個の順列があるか（0 始まりの順位）。n ≤ 20
long long perm_rank(const vector<int>& p) {
    int n = p.size();
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    vector<bool> used(n, false);
    long long r = 0;
    for (int i = 0; i < n; i++) {
        int smaller = 0;  // まだ使っていない値のうち p[i] より小さいものの数
        for (int v = 0; v < p[i]; v++) {
            if (!used[v]) smaller++;
        }
        r += smaller * fact[n - 1 - i];  // 位置 i に小さい値を置いた列はすべて前に来る
        used[p[i]] = true;
    }
    return r;
}

// 0 始まりの順位 r の順列を作る（perm_rank の逆）
vector<int> perm_kth(int n, long long r) {
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    vector<int> rest(n), p;
    iota(rest.begin(), rest.end(), 0);
    for (int i = 0; i < n; i++) {
        long long f = fact[n - 1 - i];
        int k = r / f;  // 残りの値のうち小さい方から k 番目（0 始まり）を置く
        r %= f;
        p.push_back(rest[k]);
        rest.erase(rest.begin() + k);
    }
    return p;
}
// --8<-- [end:core]

int main() {
    // 小さい n で next_permutation の順と一致するかを確かめる
    for (int n = 1; n <= 6; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long k = 0;
        do {
            assert(perm_rank(p) == k);
            assert(perm_kth(n, k) == p);
            k++;
        } while (next_permutation(p.begin(), p.end()));
    }
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto& x : p) {
        cin >> x;
        x--;
    }
    long long r = perm_rank(p);
    assert(perm_kth(n, r) == p);
    cout << r + 1 << '\n';  // 1 始まりの順位
}
