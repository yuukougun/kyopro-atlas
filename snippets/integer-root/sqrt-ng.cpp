#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long n = 67108865LL * 67108865LL - 1;  // 約 4.5 × 10^15。答えは 67108864
    long long r = (long long)sqrt((double)n);   // 真の値 67108864.99999999… が 67108865 に丸まる
    cout << r << '\n';                          // 67108865（1 大きい）
    // --8<-- [end:core]
    assert(r == 67108865LL);
    // これより小さい r では、r * r - 1 の sqrt はずれない
    for (long long s = 1; s < 67108865LL; s += 9973) {
        assert((long long)sqrt((double)(s * s - 1)) == s - 1);
    }
}
