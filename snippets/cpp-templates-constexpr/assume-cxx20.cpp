#include <bits/stdc++.h>
using namespace std;

int main() {
    int x = 3;
    [[assume(x > 0)]];  // GCC は -std=gnu++20 でも警告なしで受け付ける
    cout << x << '\n';
}
