#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int full = (1 << n) - 1;
    // --8<-- [start:core]
    // どんな集合も 1 つのグループにしてよいとき、全体を分ける方法を数える
    vector<long long> naive(1 << n, 0), fixed(1 << n, 0);
    naive[0] = fixed[0] = 1;
    for (int s = 1; s <= full; s++) {
        // 誤り：s の空でない部分集合 g をどれでも最初のグループにする
        for (int g = s; g > 0; g = (g - 1) & s) naive[s] += naive[s ^ g];
        // 正しい：s の最小の要素を含む g だけを選ぶ
        int low = s & -s, rest = s ^ low;
        for (int t = rest;; t = (t - 1) & rest) {
            fixed[s] += fixed[s ^ (t | low)];
            if (t == 0) break;
        }
    }
    // --8<-- [end:core]
    // fixed はベル数（グループの順序を区別しない）、naive は順序付きの分け方の数
    vector<long long> bell = {1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975};
    vector<long long> ordered = {1, 1, 3, 13, 75, 541, 4683, 47293, 545835, 7087261, 102247563};
    assert(n <= 10 && fixed[full] == bell[n] && naive[full] == ordered[n]);
    cout << fixed[full] << ' ' << naive[full] << '\n';
}
