#include <iostream>
#include <fstream>
#include <vector>

// NOT WORKNIG
using namespace std;

int main() {
    string brackets;
    int N;
    std::ifstream f("./0.in");
    brackets = "((()))";
    f >> N;
    N = 1;
    for (int i = 0; i < N; i++) {
        //f >> brackets;
        int bNum = brackets.size();
        vector<int> count;
        vector<int> countOpen;
        vector<int> countClose;
        if (brackets[0] == ')') {
            int j = 0;
            while (j < brackets.size() && brackets[j] == ')') j++;
            if (j == brackets.size()) {
                cout << " FASZ" << endl;
                continue;
            } else {
                brackets = brackets.substr(j, brackets.size());
            }
        }
        if (brackets[0] = ')') {
            count.push_back(-1);
            countOpen.push_back(0);
            countClose.push_back(1);
        }
        else {
            count.push_back(1);
            countOpen.push_back(1);
            countClose.push_back(0);
        }
        for (int i = 1; i < brackets.size(); i++) {
            if (brackets[i] == ')') {
                count.push_back(count.back() - 1);
                countOpen.push_back(countOpen.back());
                countClose.push_back(countClose.back() + 1);
            } else {
                count.push_back(count.back() + 1);

                if (count[i-1] <= 0 && count[i-1] < count.back()){

                }
                countOpen.push_back(countOpen.back() + 1);
                countClose.push_back(countClose.back());
            }
        }

    }
}