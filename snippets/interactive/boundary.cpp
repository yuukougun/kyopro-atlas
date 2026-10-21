#include <bits/stdc++.h>
using namespace std;

// 隠れた 0/1 の列 S_1, ..., S_N（S_1 = 0、S_N = 1）で、S_p = 0、S_{p+1} = 1 となる p を探す。
// 質問「? m」に S_m が返る。添字は問題文に合わせて 1-indexed のままにする。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // --8<-- [start:core]
    auto ask = [&](int m) {
        cout << "? " << m << endl;  // endl で書き出す（'\n' だけでは届かない）
        int r;
        cin >> r;
        if (r == -1) exit(0);       // 不正の合図を返す問題では、受け取ったらすぐ終わる
        return r;
    };
    int ng = 1, ok = n;             // 不変条件：S_ng = 0、S_ok = 1（番兵は質問しない）
    while (ok - ng > 1) {
        int mid = ng + (ok - ng) / 2;
        if (ask(mid) == 1) ok = mid;
        else ng = mid;
    }
    cout << "! " << ng << endl;
    // --8<-- [end:core]
}
