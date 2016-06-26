#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int DIAMOND = 1;
int INVALID = -2;
int PATH = 0;
int WALL = -1;

vector<vector<int>> maze;

int M;
int S;
int D;
int W;
int maxDiamonds = 0;

void printMaze(vector<vector<int>> &maze) {
    cout << endl << endl;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++)
            if (maze[i][j] != INVALID) {
                cout << i << ";" << j << ";" << maze[i][j] << " ";
            }
        cout << endl;
    }
}

void initializeMaze(bool print) {
    std::ifstream f("./10.in");
    f >> S;
    M = 2 * S - 1;
    if (print)
        cout << "M:" << M << endl;
    for (int i = 0; i < M; i++) {
        vector<int> newLine;
        for (int j = 0; j < M; j++) {
            newLine.push_back(INVALID);
        }
        if (i <= ((M) / 2)) {
            for (int j = 0; j <= i; j++) {
                newLine[j] = PATH;
            }
        } else {
            for (int j = 0; j < M - i; j++) {
                newLine[j] = PATH;
            }
        }
        maze.push_back(newLine);
    }


    f >> D;
    if (print)
        cout << "D:" << D << endl;
    int dX, dY;
    char unused;
    for (int i = 0; i < D; i++) {
        f >> dX;
        f >> unused;
        f >> dY;
        if (print)
            cout << "Diamond at: " << dX << ";" << dY << endl;
        maze[dX][dY] = DIAMOND;
    }

    f >> W;
    if (print)
        cout << "W:" << W << endl;
    int wX, wY, wZ;
    for (int i = 0; i < W; i++) {
        f >> wX;
        f >> unused;
        f >> wY;
        f >> unused;
        f >> wZ;
        if (print)
            cout << "Wall in " << wX << "th column from " << wY << " to " << wZ << endl;
        for (int j = wY; j <= wZ; j++) {
            maze[wX][j] = WALL;
        }
    }
    if (print)
        printMaze(maze);
}

int getSimpleValue(int x, int y){
    if (x >= M || x < 0)
        return -1;
    else if (y >= M || y < 0)
        return -1;
    return maze[x][y];
}

int getColumnHeight(int x){
    if (x < S) {
        return x + 1;
    } else {
        return M - x;
    }
}

int getValue(int x, int y){
    if ( x < S){
        int comeValue = std::max(getSimpleValue(x+1, y), getSimpleValue(x+1,y+1));
        if (maze[x][y] >= 0 && comeValue >= 0){
            return maze[x][y] + comeValue;
        } else {
            return -1;
        }
    } else {
        int comeValue = std::max(getSimpleValue(x+1, y-1), getSimpleValue(x+1, y));
        if (maze[x][y] >= 0 && comeValue >= 0){
            return maze[x][y] + comeValue;
        } else {
            return -1;
        }
    }
}

void goColumn(int x){
    int height = getColumnHeight(x);
    for(int i = 0; i < height; i++){
        maze[x][i] = getValue(x,i);
    }
}

void go(int x){

    for(int i = x - 1; i >= 0; i--)
        goColumn(i);
}

int main() {
    initializeMaze(false);
    go(M-1);
    //printMaze(maze);
    cout << maze[0][0];
    return 0;

}