#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    // --8<-- [start:core]
    int cnt = 0;
    for (int i = x; i > 0; i *= 2) {  // 2 倍し続けると、いつか int からあふれる（未定義動作）
        cnt++;
        if (cnt > 100) {              // 確かめるための打ち切り
            cout << "loop\n";
            return 0;
        }
    }
    cout << cnt << '\n';
    // -O0：x = 1 なら 31（あふれて負になった所で止まる）
    // -O2："loop"（あふれないと仮定して、条件 i > 0 を消してしまう）
    // --8<-- [end:core]
}
