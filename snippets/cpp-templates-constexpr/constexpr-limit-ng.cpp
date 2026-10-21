#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
constexpr int N = 1'000'000;
constexpr auto is_prime = [] {  // 10^6 までの篩をコンパイル時に作ろうとする
    array<bool, N> p{};
    for (int i = 2; i < N; i++) p[i] = true;
    for (int i = 2; (long long)i * i < N; i++)
        if (p[i])
            for (int j = i * i; j < N; j += i) p[j] = false;
    return p;
}();  // コンパイルエラー：1 つのループの回数の上限 262144 を超える
// --8<-- [end:core]

int main() { cout << is_prime[97] << '\n'; }
