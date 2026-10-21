// 重ならずに 2 回以上現れる部分文字列の最大の長さを、長さの二分探索とローリングハッシュで求める。
// 入力：N、S。出力：長さ（なければ 0）。
#include <bits/stdc++.h>
using namespace std;

const unsigned long long MOD = (1ULL << 61) - 1;

unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned __int128 t = (unsigned __int128)a * b;
    unsigned long long r = (unsigned long long)(t >> 61) + (unsigned long long)(t & MOD);
    if (r >= MOD) r -= MOD;
    return r;
}

unsigned long long random_base() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<unsigned long long>(2, MOD - 2)(rng);
}
const unsigned long long B = random_base();

struct RollingHash {
    vector<unsigned long long> h, pw;
    RollingHash(const string& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (int i = 0; i < (int)s.size(); i++) {
            h[i + 1] = mul(h[i], B) + (unsigned char)s[i];
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
            pw[i + 1] = mul(pw[i], B);
        }
    }
    unsigned long long get(int l, int r) const {
        unsigned long long x = h[r] + MOD - mul(h[l], pw[r - l]);
        if (x >= MOD) x -= MOD;
        return x;
    }
};

int brute(const string& s) {  // 確かめ用の O(N^4)
    int n = s.size(), best = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int m = 1; i + m <= j && j + m <= n; m++)
                if (s.compare(i, m, s, j, m) == 0) best = max(best, m);
    return best;
}

int main() {
    int n;
    string s;
    cin >> n >> s;
    assert((int)s.size() == n);
    RollingHash rh(s);
    // --8<-- [start:core]
    // 判定：長さ m の部分文字列で、重ならない 2 か所に現れるものがあるか（m について単調）
    auto check = [&](int m) -> bool {
        map<unsigned long long, int> first;  // ハッシュ → 最初に現れた開始位置
        for (int i = 0; i + m <= n; i++) {
            auto [it, inserted] = first.emplace(rh.get(i, i + m), i);
            if (!inserted && i - it->second >= m) return true;  // 最初の出現から m 以上離れていれば重ならない
        }
        return false;
    };
    int ok = 0, ng = n / 2 + 1;  // 長さ 0 は必ず可、n / 2 より長いと重ならずに 2 回は入らない
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        if (check(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok << '\n';
    // --8<-- [end:core]
    if (n <= 60) assert(ok == brute(s));
}
