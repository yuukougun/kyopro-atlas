// 優先順位の落とし穴：== は & より先に結合するので、mask >> i & 1 == 0 は (mask >> i) & (1 == 0) になる
#include <bits/stdc++.h>
using namespace std;

int main() {
    int mask = 0b101, zeros = 0;
    for (int i = 0; i < 3; i++) {
        if (mask >> i & 1 == 0) zeros++;             // 意図は「i ビット目が 0」だが、常に偽
    }
    cout << zeros << '\n';                           // 期待した 1 ではなく 0 が出る
}
