#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    vector<int> b = a;
    int bad = 0;
    do bad++; while (next_permutation(b.begin(), b.end()));  // ソートせずに始めると途中から

    sort(a.begin(), a.end());  // 辞書順で最小の並びから始める
    int cnt = 0;
    do cnt++; while (next_permutation(a.begin(), a.end()));
    cout << bad << ' ' << cnt << '\n';
    // --8<-- [end:core]
}
