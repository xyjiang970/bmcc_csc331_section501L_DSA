//  csc331-section_501L prog1 xin yu (jason) jiang 
//  assignment_1
//  due date sep 19, 2025

#include <iostream>
#include "personType.h"

int main() {
    // Creating personType object and setting my name:
    personType person;
    person.setName("Xin Yu (Jason)", "Jiang");
    
    /*
    std::cout << "Hello, " << person.getFirstName() << " " << person.getLastName() << std::endl;
    */
    std::cout << "Hello, ";
    person.print();
        
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
