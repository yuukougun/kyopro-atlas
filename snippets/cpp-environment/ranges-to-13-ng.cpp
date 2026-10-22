#include <bits/stdc++.h>
using namespace std;
int main() {
    auto v = views::iota(0, 3) | ranges::to<vector>(); cout << v.size() << "\\n";
}
