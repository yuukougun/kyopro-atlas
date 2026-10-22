#include <bits/stdc++.h>
using namespace std;
int main() {
    array<int, 4> d{}; mdspan m(d.data(), 2, 2); cout << m.extent(0) << "\\n";
}
