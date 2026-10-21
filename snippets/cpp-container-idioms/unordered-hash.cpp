#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:hash]
struct PairHash {
    static unsigned long long mix(unsigned long long x) {  // splitmix64
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(const pair<int, int>& p) const {
        static const unsigned long long seed =
            chrono::steady_clock::now().time_since_epoch().count();  // 実行ごとに変わる
        unsigned long long key = (unsigned long long)(unsigned)p.first << 32 | (unsigned)p.second;
        return mix(key + seed);
    }
};
// --8<-- [end:hash]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    unordered_map<pair<int, int>, int, PairHash> mp;  // 3 つ目の型引数にハッシュを渡す
    map<pair<int, int>, int> mp2;                     // map なら pair をそのままキーにできる
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mp[{x, y}]++;
        mp2[{x, y}]++;
    }
    cout << mp.size() << ' ' << mp2.size() << ' ' << mp[{1, 2}] << '\n';
}
