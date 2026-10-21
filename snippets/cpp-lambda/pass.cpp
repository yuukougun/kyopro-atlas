#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:sort]
    // 添字を a の値の小さい順に並べる。a はキャプチャで読むので引数に要らない
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    // --8<-- [end:sort]
    for (int i : idx) cout << i << ' ';
    cout << '\n';

    // --8<-- [start:check]
    // 長さ a[i] の棒を長さ x に切って k 本以上取れるか（x について単調）
    auto check = [&](long long x) {
        long long cnt = 0;
        for (long long len : a) cnt += len / x;
        return cnt >= k;
    };
    long long ok = 0, ng = 1;  // ok は「取れる」側（0 は取れるとみなす）、ng は「取れない」側
    for (long long len : a) ng = max(ng, len + 1);
    while (ng - ok > 1) {
        long long mid = (ok + ng) / 2;
        if (check(mid)) ok = mid;
        else ng = mid;
    }
    // --8<-- [end:check]
    cout << ok << '\n';
}
