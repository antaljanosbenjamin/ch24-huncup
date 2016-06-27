#include <iostream>

using namespace std;
/*
 * Explanation:
 * Create the prim-factor resolution of M, and first will the greater, and second the lesser.
 * If M is prime, then you have to comment out the second cycle. If the prim-factor resolution
 * contains more than two primes, you can easily extend the algorithm with additional function calls.
 */
unsigned long long int N = 95648216831484920;
unsigned long long int first = 2;
unsigned long long int firstCount = 0;
unsigned long long int firstExponent = 3;
unsigned long long int second = 11;
unsigned long long int secondCount = 0;
unsigned long long int secondExponent = 1;

unsigned long long int getValue(unsigned long long int oszto) {
    unsigned long long int returnValue = 0;
    for (unsigned long long int i = oszto; i < N; i *= oszto) {
        returnValue += N / i;
    }
    return returnValue;
}

int main() {
    firstCount = getValue(first);
    secondCount = getValue(second);
    cout << firstCount / firstExponent << " " << secondCount / secondExponent << endl;
    cout << std::min(firstCount / firstExponent, secondCount / secondExponent);
}
