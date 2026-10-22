// 長さ n で 1 がちょうど k 個の 0/1 列を辞書順（0 < 1）に並べたときの、
// K 番目（1-indexed）の列を作り、逆にその列が何番目かを求める。n ≤ 60 とする。
#include <bits/stdc++.h>
using namespace std;

long long C[61][61];

long long binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return C[n][k];
}

// --8<-- [start:core]
// 辞書順で K 番目（1-indexed）の列。1 ≤ K ≤ C(n, k) とする
string kth(int n, int k, long long K) {
    string s;
    for (int i = 0; i < n; i++) {
        long long c = binom(n - i - 1, k);  // ここを 0 にしたときの残りの並べ方
        if (K <= c) {
            s += '0';
        } else {
            s += '1';
            K -= c;  // 0 で始まる c 個を飛ばす
            k--;
        }
    }
    return s;
}

// 列 s が辞書順で何番目か（1-indexed）
long long rank_of(const string& s) {
    int n = s.size(), k = count(s.begin(), s.end(), '1');
    long long r = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            r += binom(n - i - 1, k);  // ここが 0 の列はすべて s より前
            k--;
        }
    }
    return r;
}
// --8<-- [end:core]

int main() {
    for (int n = 0; n <= 60; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }
    // 小さい n で、全列挙（next_permutation は辞書順に進む）と照らし合わせる
    for (int n = 0; n <= 10; n++) {
        for (int k = 0; k <= n; k++) {
            string s = string(n - k, '0') + string(k, '1');
            long long idx = 1;
            do {
                assert(kth(n, k, idx) == s);
                assert(rank_of(s) == idx);
                idx++;
            } while (next_permutation(s.begin(), s.end()));
            assert(idx - 1 == binom(n, k));
        }
    }
    int n, k;
    long long K;
    cin >> n >> k >> K;
    assert(0 <= k && k <= n && n <= 60 && 1 <= K && K <= binom(n, k));
    string s = kth(n, k, K);
    cout << s << ' ' << rank_of(s) << '\n';
}
