#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// ---- 目印より上（include の位置に出る）：宣言とクラスの定義
struct Counter {
    int c = 0;
    void add(int x);  // メンバ関数の宣言
};
int twice(int x);
template <class T> T sq(T x);
// ---- 目印より下（main の後ろに出る）：定義
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    Counter cnt;
    cnt.add(twice(n));
    cout << cnt.c + sq(3LL) << '\n';
}

// --8<-- [start:impl]
void Counter::add(int x) { c += x; }  // メンバ関数のクラスの外での定義：通る
int twice(int x) { return 2 * x; }    // 普通の関数：通る
template <class T> T sq(T x) { return x * x; }  // 関数テンプレート：通る
// --8<-- [end:impl]
