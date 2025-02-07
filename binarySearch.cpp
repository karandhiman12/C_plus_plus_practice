#include<iostream>
#include<vector>
using namespace std;
int peakValue(vector <int> &arr){
    int s = 0;
    int e = arr.size() - 1;
    int mid = s + (e-s)/2;
    while(s<e){
        if(arr[mid] < arr[mid+1]){
            s = mid+1;
        }
        else{
            e = mid;
        }
        mid = s + (e-s)/2;
    }
    return s;
}
int main(){ 
    vector <int> arr {3,4,456,897,1212,90,1};
    cout<<arr[peakValue(arr)];
   
    return 0;
}