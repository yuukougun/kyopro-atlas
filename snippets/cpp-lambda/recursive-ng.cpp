#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto fact = [&](int n) -> long long {
        if (n == 0) return 1;
        return n * fact(n - 1);  // error: use of 'fact' before deduction of 'auto'
    };
    // --8<-- [end:core]
    cout << fact(5) << '\n';
}
