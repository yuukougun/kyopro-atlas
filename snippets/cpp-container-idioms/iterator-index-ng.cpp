#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> st = {10, 20, 30};
    // --8<-- [start:core]
    int i = st.lower_bound(20) - st.begin();  // コンパイルエラー：set のイテレータは引き算できない
    // --8<-- [end:core]
    cout << i << '\n';
}
