#include <bits/stdc++.h>
using namespace std;
 
int main() {
    string s;
    cin >> s;
 
    sort(s.begin(), s.end());
 
    bool first = true;
    for (char c : s) {
        if (c == '+') continue;
        if (!first) cout << '+';
        cout << c;
        first = false;
    }
 
    return 0;
}