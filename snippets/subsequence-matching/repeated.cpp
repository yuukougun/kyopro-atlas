// S を N 回つないだ文字列に、T の各文字を k 回ずつ並べた文字列が部分列として入る最大の k を求める。
// 位置は S を無限に繰り返した列の通し番号で持ち、文字ごとの出現位置のリストで k 個先へ飛ぶ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    string s, t;
    cin >> n >> s >> t;
    long long len = s.size();
    vector<vector<long long>> pos(26);  // pos[c]：S の中で文字 c が現れる位置（昇順）
    for (int i = 0; i < len; i++) pos[s[i] - 'a'].push_back(i);
    for (char ch : t) {
        if (pos[ch - 'a'].empty()) {  // S にない文字があれば k = 0 しか入らない
            cout << 0 << '\n';
            return 0;
        }
    }
    // --8<-- [start:core]
    // 通し番号 p 以降で文字 c を k 個拾い、最後に拾った位置の次を返す。n 周を超えたら -1
    auto jump = [&](long long p, int c, long long k) -> long long {
        const auto& v = pos[c];
        long long m = v.size();
        long long copy = p / len, off = p % len;
        long long before = lower_bound(v.begin(), v.end(), off) - v.begin();
        long long idx = before + k - 1;  // この周の先頭から数えて何個目（0-indexed）を拾うか
        copy += idx / m;  // 周をまたぐ分は割り算でまとめて飛ばす
        if (copy >= n) return -1;  // 掛け算の前に打ち切り、あふれを防ぐ
        return copy * len + v[idx % m] + 1;
    };
    auto check = [&](long long k) {
        long long p = 0;
        for (char ch : t) {
            p = jump(p, ch - 'a', k);
            if (p < 0) return false;
        }
        return true;
    };
    // --8<-- [end:core]
    long long ok = 0, ng = n * len / (long long)t.size() + 1;  // k 個ずつ並べた長さは S^n を超えられない
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        (check(mid) ? ok : ng) = mid;
    }
    cout << ok << '\n';
}
