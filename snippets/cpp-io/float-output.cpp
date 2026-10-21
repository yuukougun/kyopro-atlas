#include <bits/stdc++.h>
using namespace std;

int main() {
    double x;
    cin >> x;
    double y = x / 3;
    // --8<-- [start:core]
    cout << x << ' ' << y << '\n';                     // 既定は有効数字 6 桁
    println("{} {}", x, y);                            // 元の値に戻せる最短の表記
    println("{:.15f} {:.15f}", x, y);                  // 小数点以下 15 桁
    printf("%.15f %.15f\n", x, y);
    cout << fixed << setprecision(15) << x << ' ' << y << '\n';  // 以後ずっと小数点以下 15 桁
    // --8<-- [end:core]
}
