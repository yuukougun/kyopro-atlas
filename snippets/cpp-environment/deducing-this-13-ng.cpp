#include <bits/stdc++.h>
using namespace std;
int main() {
    auto f = [](this auto&& self, int n) -> int { return n == 0 ? 0 : n + self(n - 1); }; cout << f(3) << "\\n";
}
