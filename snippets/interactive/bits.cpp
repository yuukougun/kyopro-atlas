#include <bits/stdc++.h>
using namespace std;

// N 個の候補 0, ..., N-1 のうち 1 つが当たり。M 人を選び、人 j には「番号のビット j が 1」の候補を
// まとめて渡す（質問を先に全部出す）。当たりを受け取った人だけが 1 になる文字列から番号を復元する。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // --8<-- [start:core]
    int m = 0;
    while ((1 << m) < n) m++;  // 2^m >= n となる最小の m（= ⌈log2 n⌉）
    cout << m << '\n';
    for (int j = 0; j < m; j++) {
        vector<int> group;
        for (int x = 0; x < n; x++) {
            if (x >> j & 1) group.push_back(x + 1);  // 出力は 1-indexed
        }
        cout << group.size();
        for (int x : group) cout << ' ' << x;
        cout << '\n';
    }
    cout << flush;             // 質問をまとめて出したら、答えを読む前に書き出す
    string s;                  // s[j] は人 j の結果（'1' なら当たりを受け取った）
    cin >> s;
    int ans = 0;
    for (int j = 0; j < m; j++) {
        if (s[j] == '1') ans |= 1 << j;
    }
    cout << ans + 1 << endl;
    // --8<-- [end:core]
}
