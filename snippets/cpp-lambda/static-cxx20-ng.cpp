#include <bits/stdc++.h>
using namespace std;

int main() {
    // -std=gnu++20 では警告になる（static ラムダは C++23）
    auto mul = [](long long a, long long b) static { return a * b; };
    cout << mul(3, 4) << '\n';
}
