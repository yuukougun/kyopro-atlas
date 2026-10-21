#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "ab cd";
    for (auto w : s | views::split(' ')) {
        string_view sv(w);  // -std=gnu++20 ではコンパイルエラー（C++23 から）
        cout << sv << '\n';
    }
}
