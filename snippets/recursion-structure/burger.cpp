#include <bits/stdc++.h>
using namespace std;

// レベル n のバーガー：レベル 0 はパティ P 1 枚。
// レベル n は「B・レベル n-1・P・レベル n-1・B」を下から重ねたもの。
// 下から x 枚に含まれるパティの数を求める。

// --8<-- [start:core]
long long len[51], pat[51];  // レベル n の全体の枚数・パティの数

// レベル n の下から x 枚（0 <= x <= len[n]）に含まれるパティの数
long long rec(int n, long long x) {
    if (n == 0) return x;  // x は 0 か 1
    long long res = 0;
    // 部品を下から順に見る：B, レベル n-1, P, レベル n-1, B
    if (x == 0) return res;
    x -= 1;                                   // B
    if (x <= len[n - 1]) return res + rec(n - 1, x);
    res += pat[n - 1], x -= len[n - 1];       // レベル n-1 を丸ごと
    if (x == 0) return res;
    res += 1, x -= 1;                         // P
    if (x <= len[n - 1]) return res + rec(n - 1, x);
    res += pat[n - 1];                        // レベル n-1 を丸ごと（残りは B だけ）
    return res;
}

void build(int n) {
    len[0] = 1, pat[0] = 1;
    for (int i = 1; i <= n; i++) {
        len[i] = 2 * len[i - 1] + 3;
        pat[i] = 2 * pat[i - 1] + 1;
    }
}
// --8<-- [end:core]

// 小さいレベルで実際の列を作って確かめる
string make(int n) {
    if (n == 0) return "P";
    string s = make(n - 1);
    return "B" + s + "P" + s + "B";
}

int main() {
    build(50);
    for (int n = 0; n <= 10; n++) {
        string s = make(n);
        assert((long long)s.size() == len[n]);
        long long cnt = 0;
        for (long long x = 0; x <= len[n]; x++) {
            assert(rec(n, x) == cnt);
            if (x < len[n] && s[x] == 'P') cnt++;
        }
    }
    int n;
    long long x;
    cin >> n >> x;
    cout << rec(n, x) << '\n';
}
