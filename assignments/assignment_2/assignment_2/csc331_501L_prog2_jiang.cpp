/*
csc331-section_501L prog1 xin yu (jason) jiang
assignment_2
due date Oct 10th, 2025
*/

#include <iostream>
#include <limits>
#include "book_f25.h"

int main()
{
    cout << "hello world" << endl;

    /*
    Program will wait for the user to press a key before continuing,
    which will give you time to examine your program’s output before your
    operating system closes the console window.
    */
    std::cin.clear(); // reset any error flags
    // ignore any characters in the input buffer until we find an enter character
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter key to exit..." << std::endl;
    std::cin.get(); // get one more char from the user

    return 0;
}