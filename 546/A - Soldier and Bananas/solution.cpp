#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long k, n, w;
    cin >> k >> n >> w;
 
    long long total = 0;
 
    for (int i = 1; i <= w; i++) {
        total += i * k;
    }
 
    if (total > n)
        cout << total - n;
    else
        cout << 0;
 
    return 0;
}