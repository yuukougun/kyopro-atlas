// 文字列 S の回転（先頭の k 文字を末尾へ移したもの）のうち、辞書順で最小のものを求める。
// 回転回数 k = 0, …, N-1 を全部試す。回転した文字列は作らず、添字 (k + i) mod N で読む。O(N^2)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // --8<-- [start:core]
    // 回転 k の i 文字目は s[(k + i) % n]
    auto less_rot = [&](int k1, int k2) -> bool {  // 回転 k1 は回転 k2 より小さいか
        for (int i = 0; i < n; i++) {
            char c1 = s[(k1 + i) % n], c2 = s[(k2 + i) % n];
            if (c1 != c2) return c1 < c2;  // 最初に異なる位置で決まる
        }
        return false;  // 同じ文字列
    };
    int best = 0;
    for (int k = 1; k < n; k++) {
        if (less_rot(k, best)) best = k;
    }
    string ans = s.substr(best) + s.substr(0, best);  // 最後に 1 回だけ作る
    // --8<-- [end:core]

    // A + A の長さ n の部分文字列として作った回転と照らし合わせる
    string aa = s + s, brute = s;
    for (int k = 0; k < n; k++) brute = min(brute, aa.substr(k, n));
    assert(brute == ans);
    cout << ans << '\n';
}
