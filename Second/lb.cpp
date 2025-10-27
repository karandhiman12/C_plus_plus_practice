#include <iostream>
using namespace std;

//swapping char array
void swapCharArray(char arr[], int n) {
    int l = 0, h = n - 1;
    while(l<h){
        swap(arr[l], arr[h]);
        l++;h--;
    }
}
bool checkPalindrome(char ch[], int n) {
    int l=0,h=n-1;
    while(l<=h) {
        if(ch[l] != ch[h])
            return false;
        l++;h--;
    }
    return true;
}
int main()
{
    char name[] = "Malayalam";
    cout<<boolalpha;
    int i = 0;
    while(name[i] != '\0') {
         i++;
    }
    swapCharArray(name, i);
    cout<<name<<endl;
    cout<<checkPalindrome(name,i);
    return 0;
}
