// 集合のハッシュ：数列 a と b について、a の先頭 x 項と b の先頭 y 項が
// 集合として（重複を無視して）等しいかの質問に答える。値は 1 以上 10^9 以下。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // --8<-- [start:core]
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    map<int, unsigned long long> z;  // 値ごとの乱数。a と b で同じ値には同じ乱数を使う
    for (int i = 0; i < n; i++) {
        if (!z.count(a[i])) z[a[i]] = rng();
        if (!z.count(b[i])) z[b[i]] = rng();
    }

    // ha[i] = a の先頭 i 項の集合のハッシュ。初めて出た値のときだけ XOR する（hb も同じ）
    vector<unsigned long long> ha(n + 1, 0), hb(n + 1, 0);
    set<int> seen_a, seen_b;
    for (int i = 0; i < n; i++) {
        ha[i + 1] = ha[i];
        if (seen_a.insert(a[i]).second) ha[i + 1] ^= z[a[i]];
        hb[i + 1] = hb[i];
        if (seen_b.insert(b[i]).second) hb[i + 1] ^= z[b[i]];
    }
    // --8<-- [end:core]

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        assert(0 <= x && x <= n && 0 <= y && y <= n);
        cout << (ha[x] == hb[y] ? "Yes" : "No") << '\n';
    }
}
