#include <iostream>

int sum_of_range(int m, int n) {
    int res = 0;
    for(int i=m; i <= n; i++) {
        res += i;
    }
    return res;
}
int main() {
    int m = 0, n = 0;

    std::cout<<"Enter the first number: ";
    std::cin>>m;

    std::cout<<"Enter the second number: ";
    std::cin>>n;

    std::cout<<sum_of_range(m, n)<<std::endl;

    return 0;
}