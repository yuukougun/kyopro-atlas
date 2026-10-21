#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T>
bool chmin(T& a, const T& b) {  // 型引数が 1 つの chmin
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    long long a = 10;
    chmin(a, 3);  // コンパイルエラー：a からは T = long long、3 からは T = int
}
// --8<-- [end:core]
