#include <stdlib.h>
#include <iostream>
#include <time.h>  
#include <stdexcept>
#include <stdio.h>
#include <regex>
 
using namespace std;

//checks if the string entered fits a long friendly format
bool isNumber(string aString){
    regex integer("(\\+|-)?[0-9]+", regex_constants::extended);
    return regex_match(aString,integer);
}

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
        //a regular click
        if(!flag && !isFlagged){ //click it, click it good
        isRevealed = true;
        return isBomb;
        }
        //a flag click
        if(flag){
            isFlagged = !isFlagged;  //toggle flag
            return false;
        }
    }
    //sets bomb to true
    void Bomb(){
        isBomb = true;
    }
    
};

//allocates memory for 2d array representing board
Spot** initializeBoard(int width, int height){
    Spot** board;
    board = new Spot*[width];
    for (int i = 0; i < width; i++){
        board[i] = new Spot[height];
    }

    return board;
}

//counts the number of adjacent bombs given a certain board and spot
int count(int x, int y, Spot** &aBoard, int height, int width){
    int total = 0;
    
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            //makes sure the value will not be out of index first
            if (!(x+i < 0 || x+i >= width || y+j < 0 || y+j >= height) && aBoard[x+i][y+j].isBomb){
                total++;
            }
        }
    }
    return total;
}

//adds bombs to the board and counts adjacent bombs to all spaces
void generateBoard(Spot** &aBoard, int width, int height, int bombs, int x, int y){
    srand(time(NULL));
    int bombsDropped=0;
    //drops bombs in order on board until no more remain
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
    //randomizes the location of the bombs by random swaps
    for(int i = 0 ; i < width; i++){
        for (int j = 0; j < height; j++){
            first = rand() % width;
            sec = rand() % height;
            if (!(i == x && j == y || first == x && sec == y)){
                swap(aBoard[i][j],aBoard[first][sec]);
            }
        }
    }
    //count adjacent bombs at each location
    for (int j = 0; j < width; j++){
        for (int k = 0; k < height; k++){
            if (!aBoard[j][k].isBomb){
                aBoard[j][k].value = count(j,k, aBoard, height, width);
            }
        }
    }
    
}

//given a space, uncovers that space and its surrounding spaces until the 
//surrounding spaces are >=1 instead of blank
bool reveal(Spot** &aBoard, int x, int y, int height, int width, bool flag, int &spots){
    bool result;
    //if already revealed do nothing
    if (aBoard[x][y].isRevealed){
        return false;
    }
    //if just a flag do nothing and don't uncover
    if (flag){
        return aBoard[x][y].Click(true);
    }
    //if bomb click will end the game
    else if (aBoard[x][y].isBomb){
        return aBoard[x][y].Click(false);
    }
    //if >=1 will decrease the amount of uncovered spots and click the current 
    //spot
    else if (aBoard[x][y].value != 0){
        spots--;
        return aBoard[x][y].Click(false);
    } 
    //if 0 will click that spot and also surrounding spots
    else{
    if (aBoard[x][y].value == 0 && !(aBoard[x][y].isRevealed)){
        result = aBoard[x][y].Click(false);
        spots--;
        for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            //clicking surrounding spots, first checking to make
            //sure you stay in range
            if (!(x+i < 0 || x+i >= width || y+j < 0 || y+j >= height) &&
            !(i == 0 && j == 0)){
                if(reveal(aBoard, x+i, y+j, height, width, false, spots)){
                    throw runtime_error("We done screwed up, and auto clicked a bomb :(");
                }
            }
        }
    }
    }
    //returns whether or not the click ended the game
    return result;
}
}

//deallocates memory for the 2d array representing the board
void deleteBoard(Spot** aBoard, int width){
    for (int i = 0; i < width; i++){
        delete[] aBoard[i];
    }
    delete[] aBoard;
}

//draws the a user friendly view of the current board
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
	                //bomb space
	                cout << "b";
	            }
	            else if (aBoard[x][y].value == 0){
	                //blank space
	                cout << "_";
	            }
	            else {
	                //numbered space
	                cout << aBoard[x][y].value;
	            }
	        }
	        //flagged space
	        else if (aBoard[x][y].isFlagged){
	            cout << "!";
	        }
	        else {
	            //covered space
	            cout << "X";
	        }
	        cout << "|";
	    }
	    cout << endl;
	        
	  }
}


int Play(int width, int height, int bombs){
    int x;
    string xraw;
    int y;
    string yraw;
    bool gameOver = false;
    bool flag;
    string flagraw;
    // cout << "Width ";
    // cin >> width;
    // cout << "Height ";
    // cin >> height;
    int safeSpots = height * width;
    // cout << "Bombs ";
    // cin >> bombs;
    cout << "Createing " << width << "x" << height << " board with " << bombs << " bombs" << endl;
    Spot** board = initializeBoard(width, height);
    
    while(!gameOver && safeSpots > bombs){
        drawBoard(board, width, height);
        cout << "x ";
        cin >> xraw;
        cout << "y ";
        cin >> yraw;
        if(isNumber(xraw) && isNumber(yraw)){
            x = atoi(xraw.c_str());
            y = atoi(yraw.c_str());
            if (x < width && x >=0 && y < height && y >=0){
                if (safeSpots == width * height){
                    generateBoard(board, width, height, bombs, x, y);
                    reveal(board, x, y, height, width, false, safeSpots);
                }
                else{
                    bool valid=false;
                    while(!valid){
                        cout << "flag (0 for no, 1 for yes) ";
                        cin >> flagraw;
                        if(isNumber(flagraw)){
                            valid = true;
                            flag = atoi(flagraw.c_str());
                            if (!flag && board[x][y].isFlagged){
                                cout << "You can't click a spot that has " <<
                                "been flagged. Please unflag first or click " <<
                                "a different spot" << endl;
                                continue;
                            }
                            gameOver = reveal(board, x, y, height, width, flag, safeSpots);
                        }
                    }
                }
            } else {
                cout << "Out of Bounds" << endl;
            }
        } else {
            cout << "Not a spot (try again)" << endl;
        }
    }
    for (int l = 0; l < width; l++){
        for (int m = 0; m < height; m++){
            if (board[l][m].isBomb){
                board[l][m].isRevealed = true;
            }
        }
    }
    drawBoard(board, width, height);
    if (gameOver){
        cout << "You lost!!!" << endl;
    } else if (safeSpots <= bombs){
        cout << "You won!!!" << endl;
    }
    deleteBoard(board, width);
}