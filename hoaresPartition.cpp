#include <iostream>
#include <algorithm>
using namespace std;

//hoares partition
int main(){
	int arr[] = {2,4,5,6,9,10,8,5,3,1,7};
	int n = sizeof(arr)/sizeof(arr[0]);
	stable_sort(arr,arr+n);
	for(auto i:arr)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}