#include <bits/stdc++.h>
using namespace std;

long long solve(const vector<long long>& a) {
    long long best = 0, cur = 0;
    for (long long x : a) {
        cur = max(cur + x, x);
        best = max(best, cur);
    }
    return best;
}

long long naive(const vector<long long>& a) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l + 1; r <= n; r++) {
            sum += a[r - 1];
            best = max(best, sum);
        }
    }
    return best;
}

int main() {
    int max_n, v;
    cin >> max_n >> v;  // 長さ 1〜max_n、値 -v〜v の列をすべて試す
    // --8<-- [start:core]
    for (int n = 1; n <= max_n; n++) {
        vector<long long> a(n, -v);  // 辞書順で最小の列から始める
        while (true) {
            if (solve(a) != naive(a)) {  // 短い順・辞書順で最初の反例＝最小の反例
                cout << n << '\n';
                for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
                cout << "solve " << solve(a) << ", naive " << naive(a) << '\n';
                return 0;
            }
            // 2v + 1 進数の繰り上がりの要領で次の列へ進む
            int i = n - 1;
            while (i >= 0 && a[i] == v) a[i--] = -v;
            if (i < 0) break;
            a[i]++;
        }
    }
    cout << "no difference\n";
    // --8<-- [end:core]
}
