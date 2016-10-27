#Team 2 as red team for our own project

#Applications
#1 in board.cpp
#MSC51-CPP. Ensure your random number generator is properly seeded
#In generateBoard although we should've used a number generator beside 
#rand(), we did seed well by using srand(time(NULL))

#2 in board.cpp
#MSC55-CPP. Value-returning functions must return a value from all exit paths
#The reveal function is an example of how we were sure to include a return
#no matter what if conditions were satisfied or unsatisfied

#3 in board.cpp
#MSC37-C. Ensure that control never reaches the end of a non-void function
#This is along the same lines as MSC55-CPP. If the function should return something
#it must be verified that the function will always return something regardless
#of the if statements, etc that are evaluated.

#4 in board.cpp
#DCL57-CPP. Do not let exceptions escape from destructors or deallocation functions
#In board.cpp when we created our deleteBoard Board deallocation function and Spot 
#destructors without allowing any exceptions to be thrown

#5 in board.cpp
#MSC01-C. Strive for logical completeness
# We made sure of all values that could be entered were valid by making use of the regex functions.
# In all of the functions used in board.cpp, we ensured that all unexpected conditions were handled.

#6 in board.cpp
#DCL01-C. Do not reuse variable names in subscopes
#The functions in this file use distinct and descriptive variable names
#In generateBoard the outer loop index had a different variable
#name than the inner to avoid any possible confusion

#7 in board.cpp
#DCL04-C. Do not declare more than one variable per declaration
#We declared each variable on a different line throughout

#8 in board.cpp
#DCL07-C. Include the appropriate type information in function declarators
#type information for functions declared in the function declarator rather
#than in identifier list form



#Exceptions
#1 in board.cpp
#MSC50-CPP. Do not use std::rand() for generating pseudorandom numbers
#because they can be predictable. We use rand() in generateBoard
#Changed the generateBoard function to use C++11 <random> and properly
#seeded with the system clock (MSC51-CPP)

#2 MSC04-C. Use comments consistently and in a readable fashion
#We have made use of this rec consistently throughout the code.
# changes were made to board.cpp where some improper comment lines were included.

#3 in board.cpp
#DCL15-C. Declare file-scope objects or functions that do not
#need external linkage as static
#Changed the functions in board.cpp to be static with the exception of Play
#which will be called in the separate file main



