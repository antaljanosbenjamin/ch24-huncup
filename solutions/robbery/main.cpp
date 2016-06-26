#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int WALL = -1;
int EMPTY = 0;

using namespace std;
const int N = 1000;
const int M = 1000;
const int S = 100000;
const int C = 5;
string counter = "9";

int bank[N][M];
int roomId = 0;
int depth = 0;

void printBank() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (bank[i][j] == WALL)
                cout << '*' << " ";
            else
                cout << bank[i][j] << " ";
        }
        cout << endl;
    }
}

bool canGo(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M)
        return false;
    else return bank[x][y] == EMPTY;
}

void recursiveFill(int x, int y) {
    depth++;
    bank[x][y] = roomId;
    //cout << x << " " << y << " " << depth << endl;
    if (canGo(x, y + 1)) {
        recursiveFill(x, y + 1);
    }
    if (canGo(x, y - 1)) {
        recursiveFill(x, y - 1);
    }
    if (canGo(x + 1, y)) {
        recursiveFill(x + 1, y);
    }
    if (canGo(x - 1, y)) {
        recursiveFill(x - 1, y);
    }
    depth--;
}

void fillRooms() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (canGo(i, j)) {
                roomId++;
                recursiveFill(i, j);
            }
        }
    }
}


int main() {
    std::ifstream f("./" + counter + ".in");
    int asd;
    f >> asd;
    f >> asd;
    f >> asd;
    f >> asd;
    char readed;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            f >> readed;
            if (readed == '*')
                bank[i][j] = WALL;
            else if (readed == '.') {
                // for the 10th input, you have change this lines
                //bank[i][j] = 1;
                bank[i][j] = 0;
            } else {
                cout << "BAJ";
            }
        }
    }
    // for the 10th input, you have comment this line
    fillRooms();
    roomId = 1;
    vector<int> coins(roomId, 0);
    int x;
    int y;
    for(int i = 0; i < C; i++){
        f >> x;
        f >> y;
        x--;
        y--;
        if (bank[x][y] != WALL){
            coins[bank[x][y]]++;
        }
    }


    std::ofstream out("./I" + counter + ".out",std::ios_base::out);

    for(int i = 0; i < S; i++){
        f >> x;
        f >> y;
        x--;
        y--;
        if (bank[x][y] != WALL){
            out << coins[bank[x][y]] << endl;
        }
    }

}