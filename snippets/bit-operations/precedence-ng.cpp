#include <bits/stdc++.h>
using namespace std;

// == は & より先に計算されるので、x & 1 == 0 は x & (1 == 0)、すなわち x & 0 になる
int main() {
    int x;
    cin >> x;
    if (x & 1 == 0) cout << "even\n";
    else cout << "odd\n";
    if ((x & 1) == 0) cout << "even\n";
    else cout << "odd\n";
}
