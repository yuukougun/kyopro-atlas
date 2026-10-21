#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 区間を 1 つだけ選んで符号を反転してよい（反転しなくてもよい）ときの和の最大
// 段階 0：区間の前、1：反転する区間の中、2：区間の後
long long max_after_flip(const vector<long long>& a) {
    const long long NEG = LLONG_MIN / 4;
    long long f0 = 0, f1 = NEG, f2 = NEG;
    for (long long x : a) {
        long long n0 = f0 + x;               // 区間の前：そのまま足す
        long long n1 = max(f0, f1) - x;      // 区間の中：反転して足す
        long long n2 = max({f0, f1, f2}) + x; // 区間の後：0 から直接来るのは空の区間
        f0 = n0, f1 = n1, f2 = n2;
    }
    return max({f0, f1, f2});
}
// --8<-- [end:core]

long long brute(const vector<long long>& a) {
    int n = a.size();
    long long total = accumulate(a.begin(), a.end(), 0LL);
    long long best = total;  // 反転しない
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l + 1; r <= n; r++) {
            sum += a[r - 1];
            best = max(best, total - 2 * sum);
        }
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long ans = max_after_flip(a);
    assert(ans == brute(a));
    cout << ans << '\n';
}
