#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "1 cout\n";
    println("2 println");             // C の stdout に書く
    printf("3 printf\n");             // C の stdout に書く
    cout << "4 cout\n";
    println(cout, "5 println(cout)");  // cout に書くので cout の行と順番が保たれる
    // 出力は 1・4・5・2・3 の順になる
    // --8<-- [end:core]
}
