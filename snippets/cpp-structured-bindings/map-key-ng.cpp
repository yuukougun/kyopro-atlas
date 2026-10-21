#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    map<string, int> cnt{{"a", 1}};
    for (auto& [k, v] : cnt) k += "x";  // k は const string：コンパイルエラー
    // --8<-- [end:core]
}
