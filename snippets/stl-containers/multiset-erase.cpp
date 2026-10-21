// multiset から値 x を最大 c 個消し、最大値 − 最小値を求める。
// ms.erase(x) は x と等しい要素を全部消すので、find で得たイテレータを渡して 1 個ずつ消す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// x を最大 c 個消す（x が c 個未満ならあるだけ消す）
void erase_up_to(multiset<int>& ms, int x, int c) {
    for (int k = 0; k < c; k++) {
        auto it = ms.find(x);
        if (it == ms.end()) break;  // end() を erase すると未定義動作
        ms.erase(it);               // イテレータを渡すと 1 個だけ消える
    }
}

int max_minus_min(const multiset<int>& ms) {
    assert(!ms.empty());               // 空のとき begin() と rbegin() は参照できない
    return *ms.rbegin() - *ms.begin();  // 最大は rbegin（= prev(end())）、最小は begin
}
// --8<-- [end:core]

int main() {
    multiset<int> ms = {3, 5, 5, 5, 8};
    assert(max_minus_min(ms) == 5);

    erase_up_to(ms, 5, 2);  // 5 を 2 個だけ消す
    assert(ms.count(5) == 1 && ms.size() == 3);

    erase_up_to(ms, 8, 10);  // 8 は 1 個しかないので 1 個消える
    assert(max_minus_min(ms) == 2);

    erase_up_to(ms, 7, 1);  // ない値は何も起きない
    assert(ms.size() == 2);

    // 比べるため：erase(x) は等しい要素を全部消し、消した個数を返す
    multiset<int> all = {5, 5, 5};
    size_t removed = all.erase(5);
    assert(removed == 3 && all.empty());

    // 消した個数は挿入した個数を超えないので、find と erase の回数は全体で挿入の回数以下
    cout << max_minus_min(ms) << '\n';
}
