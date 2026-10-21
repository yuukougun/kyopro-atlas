#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // --8<-- [start:core]
    cout << "? 21" << endl;  // endl は改行してから書き出す（フラッシュ）
    int r;
    cin >> r;                // 書き出していないと、相手は質問を受け取れず待ち続ける
    println("! {}", r);
    fflush(stdout);          // println・printf の後は fflush(stdout) で書き出す
    // --8<-- [end:core]
}
