#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
constexpr vector<int> v = {1, 2, 3};  // コンパイルエラー：vector は定数として残せない
// --8<-- [end:core]

int main() { cout << v[0] << '\n'; }
