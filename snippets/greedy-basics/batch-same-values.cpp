// 同じ値をまとめて処理する：使うたびに値が 1 減るものが n 個あり（初めの値 a[i] >= 0）、
// 合計 k 回まで使うときの値の合計の最大を求める。毎回最大を使う貪欲を、
// 「最大の値に並んだものを 1 段ずつまとめて下げる」形にして O(n log n) にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n >= 1 && k >= 0);
    for (int i = 0; i < n; i++) assert(a[i] >= 0);

    // --8<-- [start:core]
    sort(a.begin(), a.end(), greater<long long>());
    a.push_back(0);  // 番兵：値 0 まで下がったら、それ以上使っても増えない
    // 1 + 2 + … の形の和：上から t 段ぶん（hi, hi-1, …, hi-t+1）を w 個ずつ使ったときの合計
    auto layers = [](long long hi, long long t, long long w) {
        return (hi + (hi - t + 1)) * t / 2 * w;
    };
    long long total = 0;
    for (int i = 0; i < n && k > 0; i++) {
        long long w = i + 1;                // 今、値 a[i] に並んでいるものの個数
        long long t = a[i] - a[i + 1];      // a[i + 1] まで下げる段の数
        if (t == 0) continue;               // 次と同じ値なら、まとめて次で処理する
        if (t * w <= k) {                   // 段をすべて使い切れる
            total += layers(a[i], t, w);
            k -= t * w;
        } else {                            // 途中で回数が尽きる
            long long d = k / w;            // 丸ごと使える段の数
            total += layers(a[i], d, w);
            total += (a[i] - d) * (k % w);  // 残りの回数は次の段の一部に使う
            k = 0;
        }
    }
    cout << total << '\n';
    // --8<-- [end:core]
}
