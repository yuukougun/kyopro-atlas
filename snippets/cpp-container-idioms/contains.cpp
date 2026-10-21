#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    set<int> st = {1, 3, 5};
    multiset<int> ms = {2, 2, 2};
    map<string, int> mp = {{"ab", 1}};
    string s = "atcoder";
    // --8<-- [start:core]
    bool a = st.contains(x);            // C++20。あるかどうかだけ
    bool b = st.count(x) > 0;           // 同じ意味（C++17 まではこう書いた）
    bool c = st.find(x) != st.end();    // 同じ意味。見つけた要素を使うなら find
    bool d = ms.contains(2);            // multiset でも使える（count は個数に比例して遅い）
    bool e = mp.contains("ab");         // map はキーで調べる
    bool f = s.contains("code");        // string は C++23
    // --8<-- [end:core]
    cout << a << b << c << d << e << f << '\n';
}
