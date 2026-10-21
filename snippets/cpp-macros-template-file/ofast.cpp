// --8<-- [start:core]
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
    double x;
    cin >> x;
    double y = sqrt(x);  // x < 0 なら NaN
    cout << (isnan(y) ? "nan" : "number") << '\n';  // Ofast では NaN がないと仮定され、"number" と出る
}
// --8<-- [end:core]
