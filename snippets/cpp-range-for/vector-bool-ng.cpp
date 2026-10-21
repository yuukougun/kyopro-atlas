#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<bool> vb(3, true);
    // --8<-- [start:core]
    for (auto& b : vb) b = false;  // コンパイルエラー：要素が bool の参照ではなく一時的な代わりの物
    // --8<-- [end:core]
}
