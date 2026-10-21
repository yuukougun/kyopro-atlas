#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100000;  // 和の上限（コンパイル時の定数）

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // hist[i]：先頭の i 個から作れる和の集合。復元のために全部の段を残す
    vector<bitset<MAXS + 1>> hist(n + 1);  // vector の中身はヒープに置かれる
    hist[0][0] = 1;
    for (int i = 0; i < n; i++) hist[i + 1] = hist[i] | (hist[i] << a[i]);

    vector<int> chosen;  // 和が t になる選び方（添字）
    if (hist[n][t]) {
        int s = t;
        for (int i = n - 1; i >= 0; i--) {
            if (hist[i][s]) continue;  // a[i] を使わずに s が作れる
            chosen.push_back(i);       // 使わないと作れないので a[i] を使う
            s -= a[i];
        }
        assert(s == 0);
    }
    // --8<-- [end:core]
    if (!hist[n][t]) {
        cout << "No\n";
        return 0;
    }
    long long sum = 0;
    for (int i : chosen) sum += a[i];
    assert(sum == t);
    cout << "Yes";
    for (int k = (int)chosen.size() - 1; k >= 0; k--) cout << ' ' << chosen[k];
    cout << '\n';
}
