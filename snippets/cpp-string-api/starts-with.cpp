#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    // --8<-- [start:core]
    cout << s.starts_with("ab") << ' ';  // 先頭が "ab" か（C++20）
    cout << s.ends_with('c') << ' ';     // 末尾が 'c' か（C++20）
    cout << s.contains("bc") << '\n';    // "bc" を含むか（C++23）
    // --8<-- [end:core]
}
