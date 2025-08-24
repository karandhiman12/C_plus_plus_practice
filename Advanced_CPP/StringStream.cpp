#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> soul(string str) {
    stringstream ss(str);
    int num;
    char comma;
    vector<int> res;
    while(ss >> num) {
        res.push_back(num);
        ss >> comma;
    }
    return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string s;
    cin>>s;
    vector<int> res = soul(s);
    
    for(int i:res)
        cout<<i<<endl;
    return 0;
}
