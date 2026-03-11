#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        string ans;
        for(int i=0;i<n-1;i+=2) {
            if(s[i]=='0' && s[i+1] == '0') {
                ans.push_back('A');
            } else if(s[i]=='0' && s[i+1]=='1') {
                ans.push_back('T');
            } else if(s[i]=='1' && s[i+1] == '0') {
                ans.push_back('C');
            } else if(s[i]=='1' && s[i+1]=='1'){
                ans.push_back('G');
            }
        }
        cout<<ans<<endl;
    }

}
