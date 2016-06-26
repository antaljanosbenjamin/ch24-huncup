#include <iostream>
#include <vector>
#include <fstream>
#include <set>


// NOT WORKING
using namespace std;

enum Direction {
    LEFT_DIAGONAL_DOWN,
    LEFT_DIAGONAL_UP,
    RIGHT_DIAGONAL_DOWN,
    RIGHT_DIAGONAL_UP,
    RIGHT,
    LEFT
};
struct coord {
    int x;
    int y;
    int value;
};

vector<coord> removedItems;

Direction dirs[] = {LEFT_DIAGONAL_DOWN, LEFT_DIAGONAL_UP, RIGHT_DIAGONAL_DOWN, RIGHT_DIAGONAL_UP, RIGHT, LEFT};
int rowLengths[] = {5, 6, 7, 8, 9, 8, 7, 6, 5};
int drawed = 0;

bool canStep(int x, int y, Direction dir) {
    switch (dir) {
        case LEFT_DIAGONAL_DOWN:
            if (y < 4) {
                return true;
            } else if (x > 0 && y < 8) {
                return true;
            } else
                return false;
        case LEFT_DIAGONAL_UP:
            if (y > 4) {
                return true;
            } else if (y > 0 && x < y + 4) {
                return true;
            } else
                return false;

        case RIGHT_DIAGONAL_DOWN:
            if (y < 4) {
                return true;
            } else if (y < 8 && x + y < 12) {
                return true;
            } else
                return false;
        case RIGHT_DIAGONAL_UP:
            if (y > 4) {
                return true;
            } else if (y > 0 && x > 0) {
                return true;
            } else {
                return false;
            }
        case RIGHT:
            if (y > 4 && x + y < 12) {
                return true;
            } else if (x < y + 4 && y <= 4) {
                return true;
            } else
                return false;
        case LEFT:
            if (x > 0) {
                return true;
            } else
                return false;
        default:
            cout << "FASZ VAGY" << endl;
    }
}

bool stepIfPossible(int &x, int &y, Direction dir) {
    switch (dir) {
        case LEFT_DIAGONAL_DOWN:
            if (y < 4) {
                y++;
                return true;
            } else if (x > 0 && y < 8) {
                x--;
                y++;
                return true;
            } else
                return false;
        case LEFT_DIAGONAL_UP:
            if (y > 4) {
                x++;
                y--;
                return true;
            } else if (y > 0 && x < y + 4) {
                y--;
                return true;
            } else
                return false;

        case RIGHT_DIAGONAL_DOWN:
            if (y < 4) {
                x++;
                y++;
                return true;
            } else if (y < 8 && x + y < 12) {
                y++;
                return true;
            } else
                return false;
        case RIGHT_DIAGONAL_UP:
            if (y > 4) {
                y--;
                return true;
            } else if (y > 0 && x > 0) {
                x--;
                y--;
                return true;
            } else {
                return false;
            }
        case RIGHT:
            if (y > 4 && x + y < 12) {
                x++;
                return true;
            } else if (x < y + 4 && y <= 4) {
                x++;
                return true;
            } else
                return false;
        case LEFT:
            if (x > 0) {
                x--;
                return true;
            } else
                return false;
        default:
            cout << "FASZ VAGY" << endl;
    }
}

int table[9][9];
vector<vector<set<int>>> poss(9, vector<set<int>>(9, set<int>()));

int removeFromPoss(int fromX, int fromY, int value, bool log) {
    int removedCount = 0;
    for (int d = 0; d < 6; d++) {
        int x = fromX;
        int y = fromY;
        while (stepIfPossible(x, y, dirs[d])) {
            for (auto it = poss[x][y].begin(); it != poss[x][y].end(); it++) {
                if (*it == value) {
                    if (log) {
                        coord c{x, y, *it};
                        removedItems.push_back(c);
                    }
                    //cout << *it << " removed from poss[" << x << "][" << y << "]!" << endl;
                    poss[x][y].erase(it);
                    removedCount++;
                    break;
                }
            }
        }
    }
    return removedCount;
}

set<int> getPoss(int fromX, int fromY) {
    set<int> retPos;
    for (int i = 1; i < 10; i++) {
        retPos.insert(i);
    }
    for (int d = 0; d < 6; d++) {
        int x = fromX;
        int y = fromY;
        while (stepIfPossible(x, y, dirs[d])) {
            if (table[x][y] != 0) {
                retPos.erase(table[x][y]);
            }
        }
    }
    return retPos;
}

void printTable() {
    for (int i = 0; i < 9; i++) {
        int x = 0;
        int y = i;
        for (int j = 0; j < abs(4 - i); j++)
            cout << " ";
        cout << table[x][y] << " ";
        while (stepIfPossible(x, y, RIGHT)) {
            cout << table[x][y] << " ";
        }
        cout << endl;

    }
}


void printPoss(int x, int y) {
    cout << "poss[" << x << "][" << y << "]: ";
    for (auto it = poss[x][y].begin(); it != poss[x][y].end(); it++) {
        cout << (int) (*it) << " ";
    }
    cout << endl;
}

void printPosses() {
    for (int i = 0; i < 9; i++) {
        int x = 0;
        int y = i;
        printPoss(x, y);
        while (stepIfPossible(x, y, RIGHT)) {
            printPoss(x, y);
        }
    }
}


void addToPoss(int fromX, int fromY, int value) {
    for (int d = 0; d < 6; d++) {
        int x = fromX;
        int y = fromY;
        while (stepIfPossible(x, y, dirs[d])) {
            poss[x][y].insert(value);
        }
    }
}

void removeLesserThanMax(int row) {
    int max = 0;
    int x = 0;
    int y = row;
    while (stepIfPossible(x, y, RIGHT)) {
        if (table[x][y] != 0 && table[x][y] > max)
            max = table[x][y];
    }
    for (int i = 0; i < rowLengths[row] && max > rowLengths[row]; i++) {
        for (auto it = poss[i][row].begin(); it != poss[i][row].end(); it++) {
            if ((*it) < max - rowLengths[row] + 1)
                poss[i][row].erase(it);
        }
    }
}

void removeGreaterThanMin(int row) {
    int min = 10;
    int x = 0;
    int y = row;
    while (stepIfPossible(x, y, RIGHT)) {
        if (table[x][y] != 0 && table[x][y] < min)
            min = table[x][y];
    }
    for (int i = 0; i < rowLengths[row] && min < 10 - rowLengths[row]; i++) {
        for (auto it = poss[i][row].begin(); it != poss[i][row].end(); it++) {
            if ((*it) > min + rowLengths[i] - 1)
                poss[i][row].erase(it);
        }
    }
}


void removeRowKizart(int row) {
    removeGreaterThanMin(row);
    removeLesserThanMax(row);
}

void setItem(int x, int y, int value) {
    if (table[x][y] != 0)
        return;
    table[x][y] = value;
    drawed++;
    //cout << drawed << " " << value << endl;
    if (drawed == 61) {
        cout << "HEURÉKA" << endl;
        printTable();
        exit(111);
    }
    //int count = removeFromPoss(x,y,value,true);
    for (int i = 0; i < 9; i++) {
        int xx = 0;
        int yy = i;
        auto actualPoss = getPoss(xx, yy);
        for (auto it = actualPoss.begin(); it != actualPoss.end(); it++)
            setItem(xx, yy, *it);
        while (stepIfPossible(xx, yy, RIGHT)) {
            actualPoss = getPoss(xx, yy);
            for (auto it = actualPoss.begin(); it != actualPoss.end(); it++)
                setItem(xx, yy, *it);
        }
    }
    /*for(int i = 0; i < count; i++){
        coord c = removedItems.back();
        removedItems.pop_back();
        poss[c.x][c.y].insert(c.value);
    }
    poss[x][y] = elozoPoss;*/
    table[x][y] = 0;
    drawed--;
}

int main() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            for (int k = 1; k < 10; k++)
                poss[i][j].insert(k);

    std::ifstream f("./1.in");
    int a;
    for (int i = 0; i < 9; i++) {
        int x = 0;
        int y = i;
        f >> a;
        if (a != 0) {
            removeFromPoss(x, y, a, false);
            poss[x][y].clear();
            drawed++;
        }
        table[x][y] = a;
        while (stepIfPossible(x, y, RIGHT)) {
            f >> a;
            if (a != 0) {
                drawed++;
                removeFromPoss(x, y, a, false);
                poss[x][y].clear();
            }
            table[x][y] = a;
        }
    }
    printTable();

    for (int i = 0; i < 9; i++) {
        int x = 0;
        int y = i;
        for (auto it = poss[x][y].begin(); it != poss[x][y].end(); it++)
            setItem(x, y, *it);
        while (stepIfPossible(x, y, RIGHT)) {
            for (auto it = poss[x][y].begin(); it != poss[x][y].end(); it++)
                setItem(x, y, *it);
        }
    }
    return 0;
}


int xs[12] = {0, 0, 0, 0, 0, 2, 4, 6, 8, 6, 4, 2};
int ys[12] = {0, 2, 4, 6, 8, 8, 8, 6, 4, 2, 0, 0};

int main2() {
    for (int i = 0; i < 12; i++) {
        int x = xs[i];
        int y = ys[i];
        cout << "x: " << x << " y: " << y << endl;
        x = xs[i];
        y = ys[i];
        cout << "LEFT_DIAGONAL_UP: " << canStep(x, y, LEFT_DIAGONAL_UP) << " " <<
        stepIfPossible(x, y, LEFT_DIAGONAL_UP) << endl;
        x = xs[i];
        y = ys[i];
        cout << "LEFT_DIAGONAL_DOWN: " << canStep(x, y, LEFT_DIAGONAL_DOWN) << " " <<
        stepIfPossible(x, y, LEFT_DIAGONAL_DOWN) << endl;
        x = xs[i];
        y = ys[i];
        cout << "RIGHT_DIAGONAL_UP: " << canStep(x, y, RIGHT_DIAGONAL_UP) << " " <<
        stepIfPossible(x, y, RIGHT_DIAGONAL_UP) << endl;
        x = xs[i];
        y = ys[i];
        cout << "RIGHT_DIAGONAL_DOWN: " << canStep(x, y, RIGHT_DIAGONAL_DOWN) << " " <<
        stepIfPossible(x, y, RIGHT_DIAGONAL_DOWN) << endl;
        x = xs[i];
        y = ys[i];
        cout << "RIGHT: " << canStep(x, y, RIGHT) << " " << stepIfPossible(x, y, RIGHT) << endl;
        x = xs[i];
        y = ys[i];
        cout << "LEFT: " << canStep(x, y, LEFT) << " " << stepIfPossible(x, y, LEFT) << endl << endl << endl;
        x = xs[i];
        y = ys[i];
    }

}