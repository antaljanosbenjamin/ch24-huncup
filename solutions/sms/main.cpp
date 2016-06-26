#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

//properly calcute for any input, but print out the possible output only for one button
using namespace std;
int MODULO = 1000007;
// modify this array to watch the output with one button, eg. for 7:
char chars[] = {'p', 'q', 'r', 's', 'p', 'q', 'r', 's', 'p', 'q', 'r', 's'};
// eg. for 2:
//char chars[] = {'a','b','c','a','b','c','a','b','c','a','b','c'};
int repeats[] = {-1, 1, 3, 3, 3, 3, 3, 4, 3, 4};
vector<vector<string>> possibilities;
vector<vector<int>> possibleCount;

void initPossibleCount() {
    vector<int> zero;
    vector<int> one;
    for (int i = 0; i <= 50; i++)
        one.push_back(1);
    vector<int> two;
    possibleCount.push_back(zero);
    possibleCount.push_back(one);
    possibleCount.push_back(two);
    for (int repeat = 3; repeat <= 4; repeat++) {
        int length = 50;
        vector<int> actualCount;
        actualCount.push_back(1);
        for (int i = 1; i <= length; i++) {
            int count = 0;
            for (int j = 0; (j < repeat) && (i - j > 0); j++) {
                count += actualCount[i - j - 1];
                count %= MODULO;
            }
            if (i > repeat)
                count++;
            actualCount.push_back(count % MODULO);
            //cout << i << ".:" << count << endl;
        }
        possibleCount.push_back(actualCount);
    }
}

int main(int argc, char *args) {
    initPossibleCount();
    string input = "./";
    string output = "./M";
    input += "10.in";
    output += "10.out";
    /*for (int i = 1; i <= 4; i++){
        cout << i << ". : ";
        for(int j = 0; j < possibleCount[i].size();j++){
            cout << possibleCount[i][j] << " ";
        }
        cout << endl;
    }*/
    string sms;
    std::ifstream f(input);
    f >> sms;
    char last = sms[0];
    char length = 1;
    vector<int> possibleSequence;
    for (int i = 1; i < sms.size(); i++) {
        char actual = sms[i];
        if (actual == last) {
            length++;
        } else {
            int button = last - '0';
            int possibleCounttt = possibleCount[repeats[button]][length];
            //cout << possibleCounttt;
            possibleSequence.push_back(possibleCounttt);
            length = 1;
            last = actual;
        }
    }
    int button = last - '0';
    int possibleCounttt = possibleCount[repeats[button]][length];
    //cout << possibleCounttt << " ";
    possibleSequence.push_back(possibleCounttt);

    unsigned long long int product = possibleSequence[0];
    for (int i = 1; i < possibleSequence.size(); i++) {
        product = (product * possibleSequence[i]) % MODULO;
    }
    std::ofstream o(output, std::ios::out);
    cout << product;
    o << product;
    o.close();

    return 0;
}

int main2() {
    int repeat = 4;
    int length = 10;
    vector<string> zero;
    zero.push_back("");
    possibilities.push_back(zero);
    for (int i = 1; i <= length; i++) {
        vector<string> actual;
        for (int j = 0; j < repeat && i - j > 0; j++) {
            for (int k = 0; k < possibilities[i - j - 1].size(); k++) {
                if (possibilities[i - j - 1][k][0] != '-')
                    actual.push_back(possibilities[i - j - 1][k] + chars[j]);
            }
        }
        for (int j = repeat; j < i - 1; j++) {
            for (int k = 0; k < possibilities[i - j - 1].size(); k++) {
                if (possibilities[i - j - 1][k][0] != '-') {
                    string newString = possibilities[i - j - 1][k] + chars[j];
                    if (std::count(actual.begin(), actual.end(), newString) != 1) {
                        cout << endl << "HIBA" << endl;
                    }

                }
            }
        }
        if (i > repeat)
            actual.push_back(string("") + chars[(i - 1) % repeat]);
        cout << endl << i << ".: ";
        for (int j = 0; j < actual.size(); j++)
            cout << actual[j] << ", ";
        cout << "size: " << actual.size() << endl;
        possibilities.push_back(actual);
    }
    return 0;
}