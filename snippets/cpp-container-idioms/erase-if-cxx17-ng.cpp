#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {3, 1, 4};
    erase(v, 3);  // C++17 では std::erase がない
    cout << v.size() << '\n';
}
