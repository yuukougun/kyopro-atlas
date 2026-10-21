#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 数字列 s の部分文字列のうち、整数とみて p の倍数になるものの個数（p は 2・5 か、10 と互いに素な数）
long long count_multiples(const string& s, int p) {
    int n = s.size();
    long long ans = 0;
    if (p == 2 || p == 5) {
        // 1 の位だけで決まる：位置 i で終わる部分文字列は i + 1 個
        for (int i = 0; i < n; i++) {
            if ((s[i] - '0') % p == 0) ans += i + 1;
        }
        return ans;
    }
    // u = 接尾辞 s[i, n) の値 mod p、pw = 10^(n-1-i) mod p
    vector<long long> cnt(p, 0);
    cnt[0] = 1;  // 空の接尾辞（u_n = 0）
    long long u = 0, pw = 1;
    for (int i = n - 1; i >= 0; i--) {
        u = (u + (s[i] - '0') * pw) % p;
        pw = pw * 10 % p;
        ans += cnt[u];  // 余りが等しい右側の位置と組にする
        cnt[u]++;
    }
    return ans;
}
// --8<-- [end:core]

// 小さい入力で全部の部分文字列を調べる
long long brute(const string& s, int p) {
    int n = s.size();
    long long ans = 0;
    for (int l = 0; l < n; l++) {
        long long v = 0;
        for (int r = l; r < n; r++) {
            v = (v * 10 + (s[r] - '0')) % p;
            if (v == 0) ans++;
        }
    }
    return ans;
}

int main() {
    // 確かめ：小さい例で全探索と一致する
    assert(count_multiples("1414", 7) == 3);
    for (int p : {2, 3, 5, 7, 11, 13}) {
        for (string s : {"0", "1", "10", "2020", "1414", "5050", "3543", "9876543210"}) {
            assert(count_multiples(s, p) == brute(s, p));
        }
    }
    int n, p;
    string s;
    cin >> n >> p >> s;
    cout << count_multiples(s, p) << '\n';
}
