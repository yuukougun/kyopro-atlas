#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
auto twice(int x);  // 戻り値の型が auto の関数の宣言

int main() {
    cout << twice(3) << '\n';  // エラー：use of 'auto twice(int)' before deduction of 'auto'
}

auto twice(int x) { return 2 * x; }  // 定義は main の後ろ
// --8<-- [end:core]
