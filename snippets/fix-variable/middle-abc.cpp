#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// i < j < k で s[i] = 'A', s[j] = 'B', s[k] = 'C' となる組の数
long long count_abc(const string& s) {
    int n = s.size();
    long long right_c = 0;  // j より右にある 'C' の個数
    for (char ch : s) {
        if (ch == 'C') right_c++;
    }
    long long left_a = 0;   // j より左にある 'A' の個数
    long long ans = 0;
    for (int j = 0; j < n; j++) {
        if (s[j] == 'C') right_c--;          // j 自身は右側に入れない
        if (s[j] == 'B') ans += left_a * right_c;  // 真ん中を j に固定
        if (s[j] == 'A') left_a++;           // 次の j から見て左側に入る
    }
    return ans;
}
// --8<-- [end:core]

long long naive(const string& s) {
    int n = s.size();
    long long cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (s[i] == 'A' && s[j] == 'B' && s[k] == 'C') cnt++;
    return cnt;
}

int main() {
    // 長さ 0〜7 の A・B・C の列をすべて試して全探索と比べる
    for (int len = 0; len <= 7; len++) {
        int total = 1;
        for (int t = 0; t < len; t++) total *= 3;
        for (int code = 0; code < total; code++) {
            string s;
            int c = code;
            for (int t = 0; t < len; t++) {
                s += char('A' + c % 3);
                c /= 3;
            }
            assert(count_abc(s) == naive(s));
        }
    }
    string s;
    cin >> s;
    cout << count_abc(s) << '\n';
}
