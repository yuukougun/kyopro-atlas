#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int n;
    string line;
    cin >> n;
    getline(cin >> ws, line);   // ws で空白と改行を読み飛ばしてから 1 行読む
    // --8<-- [end:core]
    cout << n << " [" << line << "]\n";
}
