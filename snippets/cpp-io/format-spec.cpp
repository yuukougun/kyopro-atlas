#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    double x;
    cin >> n >> x;
    // --8<-- [start:core]
    cout << format("[{:5}] [{:<5}] [{:05}]\n", n, n, n);  // 幅 5 で右寄せ・左寄せ・0 埋め
    cout << format("{:b} {:08b} {:x} {:X}\n", n, n, n, n);  // 2 進・8 桁の 2 進・16 進（小文字・大文字）
    cout << format("{:.3f} [{:>8.2f}]\n", x, x);            // 小数点以下 3 桁、幅 8 で小数点以下 2 桁
    // --8<-- [end:core]
}
