#include <bits/stdc++.h>
using namespace std;

int main() {
    int limit_ms;
    cin >> limit_ms;
    // --8<-- [start:core]
    auto start = chrono::steady_clock::now();
    auto elapsed_ms = [&] {
        auto d = chrono::steady_clock::now() - start;
        return chrono::duration_cast<chrono::milliseconds>(d).count();
    };
    long long iter = 0;
    while (elapsed_ms() < limit_ms) iter++;  // 制限時間の手前まで試行を繰り返す形
    // --8<-- [end:core]
    cout << (iter > 0 && elapsed_ms() >= limit_ms ? "ok" : "ng") << '\n';
}
