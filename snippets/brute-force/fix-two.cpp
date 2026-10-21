// 2 つ決めて 3 つ目を計算する：0 ≤ x, y, z ≤ k かつ x + y + z = s となる組 (x, y, z) の数を数える。
// 3 重ループなら (k + 1)^3 回だが、x と y を決めれば z = s − x − y と決まるので (k + 1)^2 回で済む。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, s;
    cin >> k >> s;
    assert(0 <= k && k <= 2500 && 0 <= s && s <= 3 * k);

    // --8<-- [start:core]
    long long count = 0;
    for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
            int z = s - x - y;           // 残りの 1 つは計算で決まる
            if (0 <= z && z <= k) {      // 決まった値が範囲に入るかを必ず確かめる
                count++;
            }
        }
    }
    cout << count << '\n';
    // --8<-- [end:core]
}
