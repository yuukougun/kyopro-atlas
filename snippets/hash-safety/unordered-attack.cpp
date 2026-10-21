// libstdc++ の unordered_map に、置き場所（バケット）の数の倍数ばかりを入れると何が起きるかを確かめる。
// 入力：n。既定のハッシュと、実行時の乱数を混ぜたハッシュで、いちばん混んだバケットの要素数を比べる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 実行ごとに変わる値を足してから splitmix64 で混ぜる
struct SafeHash {
    static unsigned long long mix(unsigned long long x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(long long x) const {
        static const unsigned long long seed =
            chrono::steady_clock::now().time_since_epoch().count();
        return mix((unsigned long long)x + seed);
    }
};
// --8<-- [end:core]

template <class Map>
size_t max_bucket(const Map& m) {
    size_t mx = 0;
    for (size_t b = 0; b < m.bucket_count(); b++) mx = max(mx, m.bucket_size(b));
    return mx;
}

int main() {
    int n;
    cin >> n;
    assert(1 <= n && n <= 100000);
    // --8<-- [start:attack]
    assert(hash<long long>{}(12345) == 12345);  // 整数の既定のハッシュは値そのもの
    unordered_map<long long, int> probe;
    for (int i = 0; i < n; i++) probe[i] = 1;
    long long P = probe.bucket_count();  // n 個入れた後のバケットの数（素数）

    unordered_map<long long, int> plain;  // 既定のハッシュ
    unordered_map<long long, int, SafeHash> safe;
    for (int i = 1; i <= n; i++) {
        plain[i * P] = 1;  // P の倍数は、すべて P で割った余りが 0 のバケットに入る
        safe[i * P] = 1;
    }
    // --8<-- [end:attack]
    assert(plain.bucket_count() == (size_t)P);
    cout << max_bucket(plain) << '\n';                        // n になる
    cout << (max_bucket(safe) <= 10 ? "spread" : "crowded") << '\n';  // ほぼ確実に 10 以下
}
