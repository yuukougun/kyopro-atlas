// 1 秒あたりの演算回数を手元で測る。標準出力には検算用の値だけを出し、かかった時間は標準エラーに出す。
// 入力：ループの回数の基準 n（実測では n = 100000000 を与える）
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    auto timed = [&](const char* name, auto&& f) {
        auto start = chrono::steady_clock::now();
        unsigned long long r = f();
        double sec = chrono::duration<double>(chrono::steady_clock::now() - start).count();
        cerr << name << ": " << sec << " s\n";
        return r;
    };
    // --8<-- [start:core]
    // timed(名前, 関数) は関数を 1 回実行し、かかった秒数を標準エラーに出して戻り値を返す
    // (1) 前の結果に依存する掛け算と足し算を n 回（最適化で消えない）
    unsigned long long r1 = timed("arith", [&] {
        unsigned long long x = 1;
        for (long long i = 0; i < n; i++) x = x * 6364136223846793005ULL + 1442695040888963407ULL;
        return x;
    });
    // (2) 長さ m = 2^23 の配列（32 MiB）を先頭から順に読む。合わせて n 回
    const long long m = 1 << 23;
    vector<unsigned> a(m);
    for (long long i = 0; i < m; i++) a[i] = (unsigned)(i * 2654435761ULL);
    unsigned long long r2 = timed("sequential", [&] {
        unsigned long long s = 0;
        for (long long i = 0; i < n; i++) s += a[i & (m - 1)];
        return s;
    });
    // (3) 同じ配列を、乱数で決めた位置で飛び飛びに読む。合わせて n 回
    unsigned long long r3 = timed("random", [&] {
        unsigned long long s = 0, x = 1;
        for (long long i = 0; i < n; i++) {
            x = x * 6364136223846793005ULL + 1442695040888963407ULL;
            s += a[(x >> 40) & (m - 1)];
        }
        return s;
    });
    // (4) set に n / 100 個を入れ、同じ回数だけ lower_bound で探す
    unsigned long long r4 = timed("set", [&] {
        set<unsigned> st;
        long long k = n / 100;
        for (long long i = 0; i < k; i++) st.insert(a[i & (m - 1)]);
        unsigned long long s = 0;
        for (long long i = 0; i < k; i++) {
            auto it = st.lower_bound(a[(i * 7) & (m - 1)] ^ 12345u);
            if (it != st.end()) s += *it;
        }
        return s;
    });
    // --8<-- [end:core]
    cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << '\n';
}
