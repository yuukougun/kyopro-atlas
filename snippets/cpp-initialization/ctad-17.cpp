#include <bits/stdc++.h>
using namespace std;

int main() {
    vector dp(2, vector(3, 0LL));
    static_assert(is_same_v<decltype(dp), vector<vector<long long>>>);
    pair p{1, 2.5};
    static_assert(is_same_v<decltype(p), pair<int, double>>);
    priority_queue pq(greater<int>{}, vector<int>{});
    static_assert(is_same_v<decltype(pq), priority_queue<int, vector<int>, greater<int>>>);
    cout << dp.size() << '\n';
}
