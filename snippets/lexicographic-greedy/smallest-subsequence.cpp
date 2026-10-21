// 文字列 s（英小文字、長さ n）の長さ k の部分列のうち、辞書順最小のものを求める。
// 先頭から 1 文字ずつ、a から順に「その文字を選んでも残りで k 文字そろうか」を判定して決める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    assert(1 <= k && k <= n && (int)s.size() == n);

    // --8<-- [start:core]
    // nxt[i][c]：位置 i 以降で文字 c が最初に現れる位置（なければ番兵 n）。後ろから作る
    vector<array<int, 26>> nxt(n + 1);
    nxt[n].fill(n);
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
    }

    string ans;
    int pos = 0;  // 次の文字を探し始める位置
    for (int j = 0; j < k; j++) {
        // j 文字目（0-indexed）を位置 p に取ると、後ろに n - 1 - p 文字残る。
        // 残り k - 1 - j 文字が取れる条件は p <= n - k + j
        for (int c = 0; c < 26; c++) {
            int p = nxt[pos][c];  // 同じ文字なら最も前の出現を取るのが最善
            if (p <= n - k + j) {
                ans += char('a' + c);
                pos = p + 1;
                break;
            }
        }
    }
    cout << ans << '\n';
    // --8<-- [end:core]
}
