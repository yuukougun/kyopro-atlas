#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int n;
    string line;
    cin >> n;             // "3" を読み、後ろの改行は残る
    getline(cin, line);   // 残った改行までを読むので line は空
    // --8<-- [end:core]
    cout << n << " [" << line << "]\n";
}
