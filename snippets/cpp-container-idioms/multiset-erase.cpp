#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    multiset<int> ms = {1, 2, 2, 2, 3};
    multiset<int> ms2 = ms;
    // --8<-- [start:core]
    ms.erase(x);                         // x をすべて消す
    if (auto it = ms2.find(x); it != ms2.end()) {
        ms2.erase(it);                   // イテレータで消すと 1 個だけ
    }
    // --8<-- [end:core]
    cout << ms.size() << ' ' << ms2.size() << '\n';
}
