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
        isRevealed = false;
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
                if (!(i == x && j == y)){
                    aBoard[i][j].Bomb();
                    bombsDropped++;
                }
            } else {
                break;
            }
        }
        if(bombsDropped > bombs){
            break;
        }
    }
    int first;
    int sec;
    for(int i = 0 ; i < width; i++){
        for (int j = 0; j < height; j++){
            first = rand() % width;
            sec = rand() % height;
            if (!(i == x && j == y || first == x && sec == y)){
                swap(aBoard[i][j],aBoard[first][sec]);
            }
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

bool reveal(Spot** &aBoard, int x, int y, int height, int width, bool flag, int &spots){
    bool result;
    if (aBoard[x][y].isRevealed){
        return false;
    }
    if (flag){
        return aBoard[x][y].Click(true);
    }
    else if (aBoard[x][y].isBomb){
        return aBoard[x][y].Click(false);
    }
    else if (aBoard[x][y].value != 0){
        spots--;
        return aBoard[x][y].Click(false);
    } 
    else{
    if (aBoard[x][y].value == 0 && !(aBoard[x][y].isRevealed)){
        result = aBoard[x][y].Click(false);
        spots--;
        for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (!(x+i < 0 || x+i >= width || y+j < 0 || y+j >= height) &&
            !(i == 0 && j == 0)){
                if(reveal(aBoard, x+i, y+j, height, width, false, spots)){
                    throw runtime_error("We done screwed up, and auto clicked a bomb :(");
                }
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
    int width;
    int height;
    int bombs;
    int x;
    int y;
    bool gameOver;
    int safeSpots;
    bool flag;
    cout << "Width ";
    cin >> width;
    cout << "Height ";
    cin >> height;
    safeSpots = height * width;
    cout << "Bombs ";
    cin >> bombs;
    Spot** board = initializeBoard(width, height);
    
    while(!gameOver && safeSpots > bombs){
        drawBoard(board, width, height);
        cout << "x ";
        cin >> x;
        cout << "y ";
        cin >> y;
        if (safeSpots == width * height){
            generateBoard(board, width, height, bombs, x, y);
            reveal(board, x, y, height, width, false, safeSpots);
            //safeSpots--;
        }
        else{
            cout << "flag (0 for no, 1 for yes) ";
            cin >> flag;
            if (!flag && board[x][y].isFlagged){
                cout << "You can't click a spot that has " <<
                "been flagged. Please unflag first or click " <<
                "a different spot" << endl;
                continue;
            }
            gameOver = reveal(board, x, y, height, width, flag, safeSpots);
            // if (!flag){
            //     safeSpots--;
            // }
        }
    }
    if (gameOver){
        for (int l = 0; l < width; l++){
            for (int m = 0; m < height; m++){
                if (board[l][m].isBomb){
                    board[l][m].isRevealed = true;
                }
            }
        }
        drawBoard(board, width, height);
        cout << "You lost!!!" << endl;
    }
    else if (safeSpots <= bombs){
        cout << "You won!!!" << endl;
    }
    deleteBoard(board, width);
}