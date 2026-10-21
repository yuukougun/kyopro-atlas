#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
int count = 0;  // グローバル変数。std::count と区別できない
int y1;         // <cmath> の関数 y1（第 2 種ベッセル関数）と同じ名前

int main() {
    cin >> y1;   // エラー
    count++;     // エラー：reference to 'count' is ambiguous
}
// --8<-- [end:core]
