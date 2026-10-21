#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 1, 2};
    // --8<-- [start:core]
    v.erase(ranges::unique(v), v.end());  // 戻り値は subrange でイテレータではない：コンパイルエラー
    // --8<-- [end:core]
}
