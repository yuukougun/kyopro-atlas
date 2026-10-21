#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
int cnt = 0;  // グローバル変数は標準ライブラリと重ならない名前にする

int main() {
    int count = 0, y1;  // 関数の中の変数なら、外側の std::count・y1 を隠すだけで通る
    cin >> y1;
    count += y1;
    cnt += count;
    cout << cnt << '\n';
}
// --8<-- [end:core]
