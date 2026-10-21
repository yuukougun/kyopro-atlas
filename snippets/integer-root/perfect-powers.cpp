#include <bits/stdc++.h>
using namespace std;

long long isqrt(long long n) {
    long long r = sqrtl((long double)n);
    while (r > 0 && r > n / r) r--;
    while (r + 1 <= n / (r + 1)) r++;
    return r;
}

// --8<-- [start:core]
// 1 以上 n 以下で、a^b（a >= 1, b >= 2）と書ける数の個数
long long count_perfect_powers(long long n) {
    vector<long long> non_square;  // 指数 3 以上で書けて、平方数でない数
    for (long long a = 2; a <= n / a / a; a++) {  // a^3 <= n
        long long x = a * a;
        while (x <= n / a) {  // x * a <= n の間だけ掛ける
            x *= a;
            long long r = isqrt(x);
            if (r * r != x) non_square.push_back(x);
        }
    }
    sort(non_square.begin(), non_square.end());
    non_square.erase(unique(non_square.begin(), non_square.end()), non_square.end());
    return isqrt(n) + (long long)non_square.size();  // 平方数（1 を含む）＋それ以外
}
// --8<-- [end:core]

int main() {
    // 小さい n を、集合で重複を除く素朴な数え方と比べる
    set<long long> s = {1};
    long long prev = 0;
    for (long long n = 1; n <= 5000; n++) {
        for (long long a = 2; a * a <= n; a++) {
            long long x = a;
            while (x <= n / a) {
                x *= a;
                if (x == n) s.insert(x);
            }
        }
        long long cnt = (long long)s.size();
        assert(cnt >= prev);
        assert(count_perfect_powers(n) == cnt);
        prev = cnt;
    }

    long long n;
    cin >> n;
    cout << count_perfect_powers(n) << '\n';
}
