#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    cout << to_string(123) + "!" << '\n';    // 123!
    cout << to_string(3.14) << '\n';         // 3.140000（小数点以下 6 桁に固定）
    cout << to_string(1e-7) << '\n';         // 0.000000（小さい値は消える）
    cout << stoi("0042") << '\n';            // 42
    cout << stoi("12ab") << '\n';            // 12（数として読めない所で止まる）
    cout << stoll("3000000000") << '\n';     // 3000000000
    try {
        stoi("3000000000");                  // int に入らない
    } catch (const out_of_range&) {
        cout << "out_of_range\n";            // 捕まえなければ実行時エラー（RE）
    }
    // --8<-- [end:core]
}
