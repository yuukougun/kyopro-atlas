#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    println("{} {}", a, b);       // {} に引数が順に入る。最後に改行が付く
    print("{}+{}={}\n", a, b, a + b);  // print は改行を付けない
    println();                     // 改行だけ（C++26 の形。g++-15 は gnu++23 でも通す）
    println("{0} {1} {0}", a, b);  // 番号で引数を指す
    string s = format("{}-{}", a, b);  // 文字列を作るだけなら format
    cout << s << '\n';
    // --8<-- [end:core]
}
