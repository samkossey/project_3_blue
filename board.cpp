#include <stdlib.h>
#include <iostream>
#include <time.h>  

using namespace std;

struct Spot{
    int value;
    bool isBomb;
    bool isRevealed;
    bool isFlagged;
    Spot(){
        isBomb = false;
        isRevealed = false;
        isFlagged = false;
        value=0;
    };
    ~Spot(){};
    
    void Click(bool flag){
        if(!flag && !isFlagged){ //click it, click it good
        isRevealed = true;
        return isBomb;
        }
        if(flag){
            isFlagged = !isFlagged;  //toggle flag
        }
    }
    void Bomb(){
        bomb = true;
    }
    
};

Spot** initializeBoard(int width, int height){
    Spot** board;
    board = new Spot*[width];
    for (int i = 0; i < width; i++){
        board[i] = new Spot[height];
    }
    return board;
}

Spot** generateBoard(Spot** &aBoard, int width, int height, int bombs, int x, int y){
    srand(time(NULL));
    bombsDropped=0;
    for(int i = 0 ; i < width; i++){
        for (int j = 0; j < height; j++){
            if(bombsDropped <= bombs){
                aBoard[i][j]->Bomb();
            } else {
                break;
            }
        }
        if(bombsDropped > bombs){
            break;
        }
    }
    for(int i = 0 ; i < width; i++){
        for (int j = 0; j < height; j++){
            swap(aBoard[i][j],aBoard[rand() % width][rand() % height]);
        }
    }
    
    //int i = 0;
    //TODO check if x and y are in bounds ahead of time
    //aBoard[x][y].revealed = true;
    // while (i < bombs){
    //     int j = rand() % height;
    //     int k = rand() % width;
    //     if (aBoard[j][k].value == 0 && !(j == x && k == y)){
    //         aBoard[rand() % height][rand() % width].isBomb = true;
    //         i++;
    //     }
    // }
    
    for (int j = 0; j < width; j++){
        for (int k = 0; k < height; k++){
            if (!aBoard[j][k]->isBomb){
                aBoard[j][k]->value = count(j,k);
            }
        }
    }
    
    return aBoard;
}

int count(int x, int y, Spot** &aBoard, int height, int width){
    int total = 0;
    
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(x+i < 0 || x+i > width || y+j < 0 || y+j > height) && aBoard[x+i][y+j]->isBomb){
                total++;
            }
        }
    }
}

bool reveal(Spot** &aBoard, int x, int y, int height, int width){
    bool result = aBoard[x][y]->click();
    if (aBoard[x][y]->value == 0){
        for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(x+i < 0 || x+i > width || y+j < 0 || y+j > height) && aBoard[x+i][y+j]->isBomb){
                if(reveal(&aBoard, x+i, y+j, height, width)){
                    throw runtime_error("We done screwed up, and auto clicked a bomb :(");
                }
            }
        }
    }
    return result;
}

void deleteBoard(Spot** aBoard, int width){
    for (int i = 0; i < width; i++){
        delete[] aBoard[i];
    }
    delete[] aBoard;
}

int main(){
    return 0;
}