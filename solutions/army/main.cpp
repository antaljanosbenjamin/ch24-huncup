#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;
int MAX_SIZE = 1000000007;
unsigned long long int A = 54524581;
unsigned long long int B = 39625897;
unsigned long long int M = 47437387;
const unsigned long long int R = 494;
const unsigned long long int C = 403;
string counter = "10";

int PRIMES[500];

struct Coord {
    unsigned long long int i;
    unsigned long long int j;
    unsigned long long int value;
};

bool operator<(const Coord &lhs, const Coord &rhs) {
    if (lhs.value != rhs.value)
        return lhs.value < rhs.value;
    else if (lhs.i != rhs.i)
        return lhs.i < rhs.i;
    else
        return lhs.j < rhs.j;
}

bool operator>(const Coord &lhs, const Coord &rhs) {
    if (lhs.value != rhs.value)
        return lhs.value > rhs.value;
    else if (lhs.i != rhs.i)
        return lhs.i > rhs.i;
    else
        return lhs.j > rhs.j;
}

set<Coord, std::greater<Coord>> fields;
vector<unsigned long long int> groupValue;
unsigned long long int groupId = 0;
unsigned long long int floodedGroupId = 0;
unsigned long long int army[R][C];
unsigned long long int xx;
unsigned long long int yy;
unsigned long long int sumStrength = 0;
unsigned long long int lastSize = 1;

void printArmy() {
    for (unsigned long long int i = 0; i < R; i++) {
        for (unsigned long long int j = 0; j < C; j++) {
            // cout << army[i][j] << " ";
        }
        //cout << endl;
    }
}

bool canStart(unsigned long long int x, unsigned long long int y) {
    if (x < 0 || x >= R || y < 0 || y >= C)
        return false;
    else
        return army[x][y] != 0 && army[x][y] != groupId;
}

bool canFlood(unsigned long long int x, unsigned long long int y) {
    if (x < 0 || x >= R || y < 0 || y >= C)
        return false;
    else
        return army[x][y] == floodedGroupId;
}

unsigned long long int getValue(unsigned long long int x, unsigned long long int y) {
    unsigned long long int size = 1;
    set<unsigned long long int> neighbours;
    if (canStart(x - 1, y)) {
        neighbours.insert(army[x - 1][y]);
    }
    if (canStart(x + 1, y)) {
        neighbours.insert(army[x + 1][y]);
    }
    if (canStart(x, y - 1)) {
        neighbours.insert(army[x][y - 1]);
    }
    if (canStart(x, y + 1)) {
        neighbours.insert(army[x][y + 1]);
    }
    for (auto i = neighbours.begin(); i != neighbours.end(); i++) {
        size += groupValue[*i];
    }
    if (neighbours.size() == 1) {
        groupId = *neighbours.begin();
        groupValue[*neighbours.begin()] = size;
    }
    return size;
}

void floodRecursive() {
    army[xx][yy] = groupId;
    if (canFlood(xx - 1, yy)) {
        xx--;
        floodRecursive();
        xx++;
    }
    if (canFlood(xx + 1, yy)) {
        xx++;;
        floodRecursive();
        xx--;
    }
    if (canFlood(xx, yy - 1)) {
        yy--;;
        floodRecursive();
        yy++;
    }
    if (canFlood(xx, yy + 1)) {
        yy++;
        floodRecursive();
        yy--;
    }

}

void floodFrom(unsigned long long int x, unsigned long long int y) {
    if (canStart(x - 1, y)) {
        xx = x - 1;
        yy = y;
        floodedGroupId = army[xx][yy];
        floodRecursive();
    }
    if (canStart(x + 1, y)) {
        xx = x + 1;
        yy = y;
        floodedGroupId = army[xx][yy];
        floodRecursive();
    }
    if (canStart(x, y - 1)) {
        xx = x;
        yy = y - 1;
        floodedGroupId = army[xx][yy];
        floodRecursive();
    }
    if (canStart(x, y + 1)) {
        xx = x;
        yy = y + 1;
        floodedGroupId = army[xx][yy];
        floodRecursive();
    }

}

unsigned long long int current = 10000;

void setElement(unsigned long long int x, unsigned long long int y, unsigned long long int value) {
    if (army[x][y] != 0) {
        cout << "HIBA" << endl;
    }
    int newGroupId = groupId++;
    unsigned long long int size = getValue(x, y);
    if (newGroupId == groupId - 1) {
        groupValue.push_back(size);
        floodFrom(x, y);
        army[x][y] = groupId;
    } else {
        army[x][y] = groupId;
        groupId = newGroupId;
    }
    //cout << size << endl;
    for (unsigned long long int i = lastSize + 1; i <= size; i++) {
        sumStrength += value;
        //cout << i << ". strength: " << value << " " << sumStrength << endl;
        sumStrength %= MAX_SIZE;
        lastSize = size;
    }
    if (size > current) {
        cout << size << endl;
        current += 10000;
    }


}

int values[3][3] = {{1, 8, 1},
                    {7, 4, 5},
                    {1, 6, 1}};

int main() {
    std::ifstream f("./" + counter + ".in");
    std::ifstream p("./primes.txt");
    unsigned long long int asd;
    for (unsigned long long int i = 0; i < 500; i++)
        p >> PRIMES[i];
    f >> asd;
    f >> asd;
    f >> asd;
    A %= M;
    B %= M;
    for (unsigned long long int i = 0; i < 500; i++)
        PRIMES[i] %= M;
    f >> asd;
    f >> asd;
    unsigned long long int a = 0;
    unsigned long long int b = 0;
    for (unsigned long long int i = 0; i < R; i++) {
        a = (A * PRIMES[i]) % M;
        for (unsigned long long int j = 0; j < C; j++) {
            b = (B * PRIMES[j]) % M;
            Coord c;
            c.i = i;
            c.j = j;
            //c.value = values[i][j];//(a + b) % M;
            c.value = ((a + b) % M);
            fields.insert(c);
            //cout << c.value << " ";
            army[i][j] = 0;
        }
        cout << endl;
    }
    //cout << endl;
    groupValue.push_back(-1);
    for (auto it = fields.begin(); it != fields.end(); it++) {
        //printArmy();
        //cout << endl;
        setElement(it->i, it->j, it->value);
    }

    std::ofstream out("./B" + counter + ".out", std::ios_base::out);
    out << sumStrength << endl;
    //printArmy();
    //cout << sumStrength;
    return 0;

}