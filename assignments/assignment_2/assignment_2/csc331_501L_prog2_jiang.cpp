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
    book_f25 bookList; // Create book list object
    string transaction;

    while (true)
    {
        cout << "enter transaction: ";
        getline(cin, transaction);

        // Parse transaction and call appropriate methods
        char command = transaction[0];

        switch (command)
        {
        // Add book
        case 'A':
            // Parse ID and title, call bookList.addBook()
            // Display "book added" or "book not added"
            break;

        // Remove book
        case 'R':
            // Parse ID, call bookList.removeBook()
            // Display "book removed" or "book not removed"
            break;

        // Order books
        case 'O':
            // Parse ID and quantity, call bookList.orderBooks()
            // Display "books ordered" or "books not ordered"
            break;

        // Sell books
        case 'S':
            // Parse ID and quantity, call bookList.sellBooks()
            // Display "books sold" or "books not sold"
            break;

        // List books
        case 'L':
            bookList.list();
            break;

        // Quit
        case 'Q':
            return 0;
        }
    }

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