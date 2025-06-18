#include <iostream>
#include <vector>

// Sieve of Eratosthenes to print all primes up to n
void sieveOfEratosthenes(int n) {
    // Step 1: Create a boolean array "isPrime[0..n]" and initialize all entries as true.
    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not primes

    // Step 2: Eliminate non-primes by marking their multiples
    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            // Mark all multiples of p as non-prime
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // Step 3: Print all prime numbers
    std::cout << "Prime numbers up to " << n << " are:\n";
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the upper limit to find prime numbers: ";
    std::cin >> n;

    sieveOfEratosthenes(n);
    return 0;
}
