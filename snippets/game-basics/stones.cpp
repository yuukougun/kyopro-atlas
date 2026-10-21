// 石取り：石が k 個の山から、集合 a のどれかの個数を交互に取る。取れなくなった方が負け。
// win[i] = 石が i 個のとき、手番の人が勝てるか。石の少ない順に埋める。
// 先手が勝つなら、最初に取る個数（勝ちを保つ手）も出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) assert(a[i] >= 1);

    // --8<-- [start:core]
    vector<bool> win(k + 1, false);  // win[0] = false：動けないので負け
    for (int i = 1; i <= k; i++) {
        for (int x : a) {
            // 相手を負けの局面へ送れる手が 1 つでもあれば勝ち
            if (x <= i && !win[i - x]) {
                win[i] = true;
                break;
            }
        }
        // どの手も相手の勝ちの局面へ送るなら、win[i] は false（負け）のまま
    }
    // --8<-- [end:core]

    if (!win[k]) {
        cout << "Second" << '\n';
        return 0;
    }
    // --8<-- [start:move]
    // 勝ちの局面では、相手を負けの局面へ送る手を選び続ければ勝てる
    int move = -1;
    for (int x : a) {
        if (x <= k && !win[k - x]) {
            move = x;
            break;
        }
    }
    // --8<-- [end:move]
    assert(move != -1);
    cout << "First " << move << '\n';
}
