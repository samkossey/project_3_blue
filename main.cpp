#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <stdexcept>

#include "board.cpp"

using namespace std;


int main(int argc, char **argv){
        if (argc == 1){
        cout << argv[0] << " Rows Column Mines" << endl << endl;
        cout << "Description:" << endl;
        cout << "   Minesweeper CLI" << endl << endl;
        cout << "Parameter List:" << endl;
        cout << "   Rows        Number of rows for the board" << endl << endl;
        cout << "   Columns     Number of columns for the board" << endl << endl;
        cout << "   Mines       Number of mines to place on the board" << endl;
        cout << "NOTE: Number of mines should not exceed Rows x Columns - 1" << endl << endl;
        cout << "Examples:" << endl;
        cout << "   " << argv[0] << " 15 15 50" << endl;
        
        return 1;
    }
    try{
        if(argc > 4) {
            //TODO: Code for more arguments
            throw invalid_argument( "too many arguments" );
        }
        if(argc == 4){
            if(isNumber(argv[1]) && isNumber(argv[2]) && isNumber(argv[3])){
                Play(atol(argv[1]), atol(argv[2]), atol(argv[3]));
            } else {
                throw invalid_argument( "Received an invalid number" );
            }
        } else {
            throw invalid_argument( "too few arguments" );
        }
    } catch (invalid_argument const &e){
        cout << "Argument Error: " << e.what() << endl;
        return 1;
    } catch (bad_alloc const &e){
        cout << "Memory Error: " << e.what() << endl;
        return 2;
    } catch (runtime_error const &e){
        cout << "Runtime Error: " << e.what() << endl;
        return 3;
    } catch (exception const &e){
        cout << "Other Error: " << e.what() << endl;
        return 4;
    }
    //read arguments
    //while(game not done){
      //print board
      //get input
      //click the spot (reveal + initialize if not done)
      //check if bomb
      //make them loose if bomb
      //else decrement counter
    //}
    //print bomb board
    //deleteBoard
    //return if you're a LOOSER!!!! or a Winner :)
}