#include <bits/stdc++.h>
using namespace std;
// --8<-- [start:core]
// 外積 a.x * b.y - a.y * b.x を double で求める
double cross(double ax, double ay, double bx, double by) {
    return ax * by - ay * bx;
}
// --8<-- [end:core]
int main() {
    double ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    double c = cross(ax, ay, bx, by);
    cout << (c == 0 ? "0" : c > 0 ? "+" : "-") << ' ' << c << '\n';
}
