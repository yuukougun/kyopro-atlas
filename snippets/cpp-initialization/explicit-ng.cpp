#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    // --8<-- [start:core]
    atcoder::dsu d = 5;   // コンストラクタが explicit なのでコンパイルエラー
    // --8<-- [end:core]
    cout << d.size(0) << '\n';
}
