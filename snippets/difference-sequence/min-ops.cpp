#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 差分列 d[0..n]（a[-1] = a[n] = 0 として d[i] = a[i] - a[i-1]）
vector<long long> diff(const vector<long long>& a) {
    int n = a.size();
    vector<long long> d(n + 1);
    for (int i = 0; i <= n; i++) {
        long long cur = (i < n ? a[i] : 0);
        long long prev = (i > 0 ? a[i - 1] : 0);
        d[i] = cur - prev;
    }
    return d;
}

// すべて 0 の列から、区間に +1 する操作だけで a（各要素 0 以上）を作る最小回数
long long min_ops_add(const vector<long long>& a) {
    long long res = 0;
    for (long long x : diff(a)) res += max(x, 0LL);
    return res;
}

// 区間に +1 か -1 をする操作で a をすべて 0 にする最小回数（d の和は 0）
long long min_ops_add_sub(const vector<long long>& a) {
    long long res = 0;
    for (long long x : diff(a)) res += abs(x);
    return res / 2;
}

// 長さちょうど k の区間に +1 か -1 をする操作で a をすべて 0 にする最小回数（できなければ -1）
// 操作 [l, l + k) は d[l] と d[l + k] を変えるので、添字を k で割った余りごとの鎖に分かれる
long long min_ops_len_k(const vector<long long>& a, int k) {
    vector<long long> d = diff(a);
    int n = a.size();
    long long res = 0;
    for (int r = 0; r < k && r <= n; r++) {
        long long carry = 0;  // 鎖の先頭からの和 = 次の辺を通して運ぶ量
        for (int i = r; i <= n; i += k) {
            carry += d[i];
            if (i + k <= n) res += abs(carry);
        }
        if (carry != 0) return -1;  // 鎖の和が 0 でなければ作れない
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // 素朴な確かめ：長さ 1 の区間の操作は 1 点の ±1 なので、回数は |a_i| の和
    if (k == 1) {
        long long s = 0;
        for (long long x : a) s += abs(x);
        assert(min_ops_len_k(a, 1) == s);
    }
    bool nonneg = all_of(a.begin(), a.end(), [](long long x) { return x >= 0; });
    cout << (nonneg ? min_ops_add(a) : -1) << ' ' << min_ops_add_sub(a) << ' ' << min_ops_len_k(a, k) << '\n';
}
