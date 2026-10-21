#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3};
    // --8<-- [start:core]
    const vector<int>& c = a;
    c.push_back(4);  // コンパイルエラー：const の参照からは書き換えられない
    // --8<-- [end:core]
}
