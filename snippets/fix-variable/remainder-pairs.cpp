#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// i < j で (a[i] + a[j]) が m の倍数になる組の数（a[i] ≥ 0）
long long count_pairs(const vector<long long>& a, int m) {
    vector<long long> cnt(m, 0);  // cnt[r]：これまでに見た、余りが r の要素の個数
    long long ans = 0;
    for (long long x : a) {
        int r = x % m;
        int need = (m - r) % m;   // 相手に要る余り（r = 0 なら 0）
        ans += cnt[need];         // x を右の要素 j に固定し、左の i を数える
        cnt[r]++;                 // 数えてから入れるので、自分自身とは組まない
    }
    return ans;
}
// --8<-- [end:core]

long long naive(const vector<long long>& a, int m) {
    long long c = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++)
            if ((a[i] + a[j]) % m == 0) c++;
    return c;
}

int main() {
    // 小さい入力をすべて試して全探索と比べる
    for (int m = 1; m <= 4; m++) {
        for (int len = 0; len <= 5; len++) {
            int total = 1;
            for (int t = 0; t < len; t++) total *= 6;
            for (int code = 0; code < total; code++) {
                vector<long long> a;
                int c = code;
                for (int t = 0; t < len; t++) {
                    a.push_back(c % 6);
                    c /= 6;
                }
                assert(count_pairs(a, m) == naive(a, m));
            }
        }
    }
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << count_pairs(a, m) << '\n';
}
