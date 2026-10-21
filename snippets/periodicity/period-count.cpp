#include <bits/stdc++.h>
using namespace std;

// 周期 P の模様 pat（'#' が黒）を整数の位置全体に並べたとき（位置 i の色は pat[i mod P]）、
// 半開区間 [L, R) にある黒の数を答える。L, R は負でもよい。
int main() {
    int P, Q;
    string pat;
    cin >> P >> pat >> Q;

    // --8<-- [start:core]
    vector<long long> pre(P + 1, 0);  // pre[r] = pat[0..r) の黒の数
    for (int i = 0; i < P; i++) pre[i + 1] = pre[i] + (pat[i] == '#');

    auto floor_div = [](long long a, long long b) -> long long {  // b > 0
        long long q = a / b;
        if (a % b < 0) q--;  // C++ の / は 0 方向へ丸めるので、負なら 1 つ下げる
        return q;
    };
    // f(X) = [0, X) の黒の数。X < 0 でも f(X + P) = f(X) + pre[P] を保つように延ばす
    auto f = [&](long long X) -> long long {
        long long q = floor_div(X, P);
        long long r = X - q * P;  // 0 <= r < P
        return q * pre[P] + pre[r];
    };
    // --8<-- [end:core]

    for (int i = 0; i < Q; i++) {
        long long L, R;
        cin >> L >> R;
        cout << f(R) - f(L) << '\n';
    }
}
