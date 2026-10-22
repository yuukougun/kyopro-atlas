#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;
int main() {
    // --8<-- [start:core]
    rlimit r;
    getrlimit(RLIMIT_STACK, &r);
    if (r.rlim_cur == RLIM_INFINITY) cout << "unlimited\n";
    else cout << r.rlim_cur / 1024 << " KiB\n";
    // --8<-- [end:core]
}
