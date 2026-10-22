#include <bits/stdc++.h>
using namespace std;

// 値の上限は 2×10^5。各ケースの A に現れる値の種類数と、最も多い値の個数を答える。
const int MAX_V = 200000;
int cnt[MAX_V + 1];  // グローバルなので最初は 0。ケースをまたいで使い回す

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    // --8<-- [start:core]
    for (int tc = 0; tc < t; tc++) {
        int n;
        cin >> n;
        vector<int> a(n);  // ケースの中で作れば、毎回空から始まる
        for (int i = 0; i < n; i++) cin >> a[i];

        int kinds = 0, best = 0;
        for (int x : a) {
            if (cnt[x] == 0) kinds++;
            cnt[x]++;
            best = max(best, cnt[x]);
        }
        cout << kinds << ' ' << best << '\n';

        // 使い回す配列は、使った添字だけを 0 に戻す（全体を埋めると T 倍の時間がかかる）
        for (int x : a) cnt[x] = 0;
    }
    // --8<-- [end:core]
    for (int v = 0; v <= MAX_V; v++) assert(cnt[v] == 0);
}
