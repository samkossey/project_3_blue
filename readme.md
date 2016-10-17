# Project 3 Blue

# Command Line Minesweeper

# Trevor Buttrey, Sam Kossey, Ishaani Priyadarshini, Nitya Krishnan

# Compile line: g++-4.9 main.cpp -std=c++11
# Run: ./a.out row# col# mine#


# The following are the rules and recs we have considered for the project.
# 1)  EXP53-CPP. Do not read uninitialized memory.This is evident from the lines-15-18,40, 49, 62, 83,84 and 126 in board.cpp.
# 2)  EXP51-CPP. Do not delete an array through a pointer of the incorrect type. There is a destructor for deinitializing the spot, which is for creating space. So instead of including a free or delete, we create a destructor.
# 3)  ARR32-C. Ensure size arguments for variable length arrays are in a valid range. For creating the board, we have ensured an i*j matrix with proper integer bounds. It is evident from void generateBorad, line 61 in board.cpp.
# 4)  ARR01-C. Do not apply the sizeof operator to a pointer when taking size of an arrays. We have made use of double pointer to ensure space on the board. Sizeof operator is something we did not include for this one.
# 5)  EXP54-CPP. Do not access an object outside its lifetime. In all the operations that need an object to be created, the object has been called within the scope of the function which is the lifetime of the object.
// # 6)  EXP34-C. Do not deference null pointers. doesn't apply
# 7)  EXP37-C. Call functions with the correct number and type of arguments. All the functions have been called with correct number and type of arguments. 
# 8)  EXP45-C. Do not perform assignments in selection statements.We took care of this rec in lines 67, 85,131, 166, 210 in board.cpp.
# 9)  EXP19-C. Use braces for the body of an if, for or while statement. We have ensured that for the body of if, for and while statements, we have included proper braces.
# 10) EXP20-C. Perform explicit tests to determine success, true, false and equality. In the function bool reveal at line 113 in board.cpp we have created sufficient conditions for checking the equality.
# 11) EXP15-C. Do not place a semicolon on the same line as an if, for or while statement. We have taken care to not include the statement delimiter in the same line as an if for and while statements as they are not exit controlled structures.
# 12) EXP35-C. Do not modify objects with a temporary lifetime. No objects with temporary lifetime have been modified.
# 13) EXP40-C. Do not modify constant objects. Constant objects have been constant throughout the program.
// # 14) EXP46-C. Do not use a bitwise operator with Boolean like operand. 
# 15) ARR38-C. Guarantee that library functions do not form invalid pointers.
# 16) EXP00-C. Use paranthesis for precedence of operation. In all the files it has been taken care that proper paranthesis are used operations.