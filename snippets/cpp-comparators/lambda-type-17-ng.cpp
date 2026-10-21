#include <bits/stdc++.h>
using namespace std;

int main() {
    auto cmp = [](int x, int y) { return x > y; };
    set<int, decltype(cmp)> st;  // C++17 ではコンパイルエラー（ラムダの型は既定の構築ができない）
    st.insert(1);
}
