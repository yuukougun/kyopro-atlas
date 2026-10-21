#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << (x) << endl
#else
#define debug(x) (void)0  // 提出では何もしない（引数も評価しない）
#endif
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    long long s = 0;
    for (int i = 1; i <= n; i++) {
        s += i;
        debug(s);  // g++ -DLOCAL のときだけ標準エラー出力に出る
    }
    cout << s << '\n';
}
