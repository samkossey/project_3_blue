#include <stdlib.h>
#include <iostream>
#include <time.h>  
#include <stdexcept>
#include <stdio.h>
 
using namespace std;

struct Spot{
    int value;
    bool isBomb;
    bool isRevealed;
    bool isFlagged;
    Spot(){
        isBomb = false;
        isRevealed = true;
        isFlagged = false;
        value = 0;
    };
    ~Spot(){};
    
    bool Click(bool flag){
        if(!flag && !isFlagged){ //click it, click it good
        isRevealed = true;
        return isBomb;
        }
        if(flag){
            isFlagged = !isFlagged;  //toggle flag
            return false;
        }
    }
    void Bomb(){
        isBomb = true;
    }
    
};

Spot** initializeBoard(int width, int height){
    Spot** board;
    board = new Spot*[width];
    for (int i = 0; i < width; i++){
        board[i] = new Spot[height];
    }
    for (int j = 0; j < width; j++){
        for (int k = 0; k < height; k++){
            cout << board[j][k].value;
        }
        cout << endl;
    }
    return board;
}

int count(int x, int y, Spot** &aBoard, int height, int width){
    int total = 0;
    
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(x+i < 0 || x+i >= width || y+j < 0 || y+j >= height) && aBoard[x+i][y+j].isBomb){
                total++;
            }
        }
    }
    return total;
}

void generateBoard(Spot** &aBoard, int width, int height, int bombs, int x, int y){
    srand(time(NULL));
    int bombsDropped=0;
    for(int i = 0 ; i < width; i++){
        for (int j = 0; j < height; j++){
            if(bombsDropped < bombs){
                aBoard[i][j].Bomb();
                    bombsDropped++;
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
            if (!aBoard[j][k].isBomb){
                aBoard[j][k].value = count(j,k, aBoard, height, width);
            }
        }
    }
    
}

bool reveal(Spot** &aBoard, int x, int y, int height, int width){
    bool result = aBoard[x][y].Click(false);
    if (aBoard[x][y].value == 0){
        for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(x+i < 0 || x+i > width || y+j < 0 || y+j > height) && aBoard[x+i][y+j].isBomb){
                if(reveal(aBoard, x+i, y+j, height, width)){
                    throw runtime_error("We done screwed up, and auto clicked a bomb :(");
                }
            }
        }
    }
    return result;
}
}

void deleteBoard(Spot** aBoard, int width){
    for (int i = 0; i < width; i++){
        delete[] aBoard[i];
    }
    delete[] aBoard;
}

void drawBoard(Spot** &aBoard, int width, int height){
	cout << " _";
	for (int i = 0; i < width; i++)
	{
		cout << i << "_";
	}
	cout << endl;
	
	for (int y = 0; y < height; y++){
	    cout << y << "|";
	    for (int x = 0; x < width; x++){
	        if (aBoard[x][y].isRevealed){
	            if (aBoard[x][y].isBomb){
	                cout << "b" << "|";
	            }
	            else if (aBoard[x][y].value == 0){
	                cout << "_" << "|";
	            }
	            else {
	                cout << aBoard[x][y].value << "|";
	            }
	        }
	        else if (aBoard[x][y].isFlagged){
	            cout << "!" << "|";
	        }
	        else {
	            cout << "0" << "|";
	        }
	    }
	    cout << endl;
	        
	  }
}


int main(){
    Spot** board = initializeBoard(5, 5);
    generateBoard(board, 5, 5, 2, 0, 0);
    drawBoard(board, 5, 5);
    deleteBoard(board, 5);
}