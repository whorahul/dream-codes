//Language: C++
//by Rahul Balamwar

#include <bits/stdc++.h>

using namespace std;

inline void JadedBeast() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}
const int MAX =1e4;

//hackerrank.com/whorahul

int main() {
    JadedBeast();
    double b,u0,u1;
    cin >> u0>>b;
    cout.precision(15);
    u1=pow(10,-9)*floor(pow(2,b-pow(u0,2)));
    for(int i=1 ; i<=MAX ;i++){
        u0=u1;
        u1=pow(10,-9)*floor(pow(2,b-pow(u0,2)));
        

    }
    double result=u0+u1;
    cout<<result;


    
}
