#include <bits/stdc++.h>
using namespace std;
 
int main() {
    string s;
    cin >> s;
 
    int upper = 0, lower = 0;
 
    for (char c : s) {
        if (isupper(c))
            upper++;
        else
            lower++;
    }
 
    for (char &c : s) {
        if (upper > lower)
            c = toupper(c);
        else
            c = tolower(c);
    }
 
    cout << s;
 
    return 0;
}