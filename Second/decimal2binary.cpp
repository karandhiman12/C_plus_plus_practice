#include <iostream>
#include <string>
using namespace std;

string decimal2binary(int num) {
    //Time Complexity = O(log2N)
    //Space Complexity = O(log2N)
    string result = "";
    while(num!=0) {
        if(num%2 == 1) {
            result += '1';
        } else {
            result += '0';
        }
        num = num/2;
    }
    int l = 0, h = result.size()-1;
    while(l<h) {
        swap(result[l],result[h]);
        l++;h--;
    }
    return result;
}
int binary2decimal(string str) {
    int res = 0;
    int n = str.size();
    int pow = 1;
    for(int i=n-1;i>=0;i--) {
        if(str[i] == '1')
            res += pow;
        pow *= 2;
    }
    return res;
}
int main() {
    cout<<decimal2binary(35);
    cout<<endl;
    cout<<binary2decimal("1011");
    return 0;
}