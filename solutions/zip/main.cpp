#include <iostream>

using namespace std;
//only for first zip, calculate the password
unsigned long long int tomb[35];
int main() {
    tomb[0] = 1;
    for(unsigned long long int i = 1; i < 35; i++ ){
        unsigned long long int sum = 0;
        for(int j = 0; j < i; j++)
            sum+=tomb[j];
        tomb[i] = sum * 2 + 1 + ( (i % 2) * 2);
        cout << tomb[i] << endl;
    }
}