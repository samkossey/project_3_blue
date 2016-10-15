#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){
        if (argc == 1){
        cout << argv[0] << " Rows Column Mines" << endl << endl;
        cout << "Description:" << endl;
        cout << "   Minesweeper CLI" << endl << endl;
        cout << "Parameter List:" << endl;
        cout << "   Rows        Number of rows for the board" << endl << endl;
        cout << "   Columns     Number of columns for the board" << endl << endl;
        cout << "   Mines       Number of mines to place on the board"
        cout << "NOTE: Number of mines should not exceed Rows x Columns - 1" << endl << endl;
        cout << "Examples:" << endl;
        cout << "   " << argv[0] << " 15 15 50" << endl;
        
        return 1;
    }
    try{
        if(argc > 3) {
            //TODO: Code for more arguments
            throw invalid_argument( "too many arguments" );
        }
        if(argc >= 3){
            File* file1 = new File(argv[1]);
            File* file2 = new File(argv[2]);
            string file1content = file1->readfile();
            string file2content = file2->readfile();
            delete(file1);
            delete(file2);
            
            list<string> file1list = parseText(file1content);
            list<string> file2list = parseText(file2content);
            
            list<long> file1long = stringToLong(file1list);
            list<long> file2long = stringToLong(file2list);
            
            cout << "Input 1: " << file1content << endl;
            cout << "Input 2: " << file2content << endl;
            cout << "Output : ";
            PollyAdd(file1long, file2long);
            
            //printing
            // for (long i: file1long){
            //     cout << "\"" << i << "\"" << endl;
            // }
            // for (long j: file2long){
            //     cout << "\"" << j << "\"" << endl;
            // }
            // for (string i: file1list){
            //     cout << "\"" << i << "\"" << endl;
            // }
            // for (string j: file2list){
            //     cout << "\"" << j << "\"" << endl;
            // }
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