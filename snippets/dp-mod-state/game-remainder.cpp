// 後ろから余りごとの勝敗を決める：数字列 s と手番の列 t（各手で 'T' か 'A'）が与えられる。
// 0 から始め、i 手目は t[i] の人が「x を 10x + s[i] にする」か「x を 10x にする」かを選ぶ。
// 最後の x が m の倍数なら T の勝ち、そうでなければ A の勝ち。両者が最適に動いたときの勝者を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    assert(1 <= m && (int)s.size() == n && (int)t.size() == n);

    // --8<-- [start:core]
    // win[i][r] ＝ i 手を終えて x mod m = r のとき、ここから両者が最適に動いて T が勝つか
    vector win(n + 1, vector<bool>(m, false));
    win[n][0] = true;  // 終局：余り 0 なら T の勝ち
    for (int i = n - 1; i >= 0; i--) {  // 後ろの手から決める
        int c = s[i] - '0';
        for (int r = 0; r < m; r++) {
            bool w1 = win[i + 1][(r * 10 + c) % m];  // s[i] を付ける
            bool w0 = win[i + 1][(r * 10) % m];      // 0 を付ける
            win[i][r] = (t[i] == 'T') ? (w1 || w0)   // T はどちらかで勝てればよい
                                      : (w1 && w0);  // A がどちらを選んでも T が勝つときだけ
        }
    }
    cout << (win[0][0] ? "T" : "A") << '\n';
    // --8<-- [end:core]
}
