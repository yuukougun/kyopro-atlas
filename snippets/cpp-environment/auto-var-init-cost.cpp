#include <bits/stdc++.h>
using namespace std;
// --8<-- [start:core]
// 呼ぶたびに大きな局所配列を宣言し、先頭の k 個だけを使う
long long f(int k, int x) {
    int buf[100000];
    for (int i = 0; i < k; i++) buf[i] = x + i;
    long long s = 0;
    for (int i = 0; i < k; i++) s += buf[i];
    return s;
}
// --8<-- [end:core]
int main() {
    int q, k;
    cin >> q >> k;
    assert(0 <= k && k <= 100000);
    long long s = 0;
    for (int i = 0; i < q; i++) s += f(k, i);
    cout << s << '\n';
}
