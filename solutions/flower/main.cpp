#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

//NOT WORKING
using namespace std;

int BOUQUET_SIZE;
int FLOWER_TYPES;
int* array;

void recursiveGenerate(int depth){
    if (depth == BOUQUET_SIZE){
        for(int i = 0; i < BOUQUET_SIZE; i++){
            cout << array[i] << " ";
        }
        cout << endl;
    }
    for(int i = array[depth - 1]; i < FLOWER_TYPES - BOUQUET_SIZE + 1 + depth; i++){

    }
};

void startGenerate(){
    for(int i=1; i <= FLOWER_TYPES - BOUQUET_SIZE + 1; i++ ){
        array[0] = i;
        recursiveGenerate(1);
    }
}
int main() {

    std::ifstream f("./10.in");
    f >> BOUQUET_SIZE;
    f >> FLOWER_TYPES;
    array = new int[BOUQUET_SIZE];
    startGenerate();
    return 0;

}