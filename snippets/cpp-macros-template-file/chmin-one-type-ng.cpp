#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? (a = b, true) : false;
}

int main() {
    long long mn = 1LL << 60;
    chmin(mn, 0);  // エラー：T が long long と int の両方に推論されて決まらない
}
// --8<-- [end:core]
