#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:bad]
    vector<int> v = {1};
    int& r = v[0];
    v.push_back(2);    // 容量 1 が足りず再確保が起きる
    cout << r << '\n'; // 未定義動作：r は解放されたメモリを指す
    // --8<-- [end:bad]
}
