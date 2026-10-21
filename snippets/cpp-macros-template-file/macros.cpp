#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) (v).begin(), (v).end()
template <class T> using vc = vector<T>;
template <class T> using vvc = vector<vc<T>>;

// 引数の数で FOR1〜FOR3 を選ぶ：引数の後ろに候補を並べ、4 番目に来た名前を使う
#define FOR1(n) for (long long _i = 0; _i < (n); _i++)
#define FOR2(i, n) for (long long i = 0; i < (n); i++)
#define FOR3(i, a, b) for (long long i = (a); i < (b); i++)
#define PICK(a, b, c, d, ...) d
#define FOR(...) PICK(__VA_ARGS__, FOR3, FOR2, FOR1, _)(__VA_ARGS__)
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vc<int> a(n);
    rep(i, n) cin >> a[i];
    sort(all(a));  // sort(a.begin(), a.end());
    long long sum = 0;
    FOR(i, n) sum += a[i];       // FOR2
    FOR(i, 1, n) sum += a[i];    // FOR3
    int k = 0;
    FOR(3) k++;                  // FOR1
    vvc<int> g(2);
    assert(k == 3 && g.size() == 2);
    cout << sum << '\n';
}
