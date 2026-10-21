#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 段階 0：区間の前、1：区間の中、2：区間の後。区間は空でないとする
long long max_subarray(const vector<long long>& a) {
    const long long NEG = LLONG_MIN / 4;    // 来られない状態（-∞）
    long long f0 = 0, f1 = NEG, f2 = NEG;   // 直前の位置が段階 p にあるときの和の最大
    for (long long x : a) {
        long long n0 = f0;                  // まだ区間の前（x は使わない）
        long long n1 = max(f0, f1) + x;     // 0 から入る、または 1 を続ける
        long long n2 = max(f1, f2);         // 1 から出る、または 2 を続ける
        f0 = n0, f1 = n1, f2 = n2;
    }
    return max(f1, f2);                     // 区間に 1 回は入った状態だけが答え
}
// --8<-- [end:core]

long long brute(const vector<long long>& a) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l + 1; r <= n; r++) {
            sum += a[r - 1];
            best = max(best, sum);
        }
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long ans = max_subarray(a);
    assert(ans == brute(a));
    cout << ans << '\n';
}
