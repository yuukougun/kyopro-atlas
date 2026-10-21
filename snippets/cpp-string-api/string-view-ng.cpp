#include <bits/stdc++.h>
using namespace std;

string make(int n) { return string(n, 'x'); }

// 呼ぶと未定義動作になるので main からは呼ばない（-fsanitize=address を付けて呼ぶと heap-use-after-free で止まる）
void bad() {
    // --8<-- [start:core]
    string_view sv = make(100);      // 一時的な string は、この行の終わりで消える
    cout << sv[0] << '\n';           // 消えたメモリを読む（未定義動作）。-Wall -Wextra でも警告は出ない
    // --8<-- [end:core]
}

int main() {}
