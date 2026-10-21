#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

int main() {
    // --8<-- [start:core]
    dsu d = 5;  // コンパイルエラー：コンストラクタが explicit
    // --8<-- [end:core]
    cout << d.size(0) << '\n';
}
