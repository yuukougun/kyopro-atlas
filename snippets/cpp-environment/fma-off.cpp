#include <bits/stdc++.h>
using namespace std;
double cross(double ax, double ay, double bx, double by) {
    return ax * by - ay * bx;
}
int main() {
    double ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    double c = cross(ax, ay, bx, by);
    cout << (c == 0 ? "0" : c > 0 ? "+" : "-") << ' ' << c << '\n';
}
