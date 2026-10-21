#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {3, 1, 4};
    for (auto i : views::indices(v.size())) cout << v[i] << '\n';  // -std=gnu++26 でも GCC 15 にはない
}
