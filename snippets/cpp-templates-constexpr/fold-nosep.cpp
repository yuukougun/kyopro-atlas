#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class... Ts>
void print_all(const Ts&... xs) {
    (cout << ... << xs) << '\n';  // 区切りなしで続けて出る：1, 23, "ab" → 123ab
}
// --8<-- [end:core]

int main() { print_all(1, 23, "ab"); }
