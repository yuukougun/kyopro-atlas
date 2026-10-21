#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    ios::sync_with_stdio(false);  // C の stdio との同期を切る（cin・cout が自前のバッファを使う）
    cin.tie(nullptr);             // cin で読む前に cout を書き出す動作を切る
    int n;
    cin >> n;
    long long s = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s += x;
    }
    cout << s << '\n';
    // --8<-- [end:core]
}
