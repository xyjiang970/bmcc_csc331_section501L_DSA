/*
Xin Yu (Jason) Jiang
CSC331, Section: 501L
Assignment 2
Due Date: Oct 10th, 2025

Program Name: csc331_501L_prog2_jiang_web.cpp

MODIFICATION FOR WEB: Added processTransaction() and getBookList()
functions to expose functionality to JavaScript.
All original logic remains unchanged.

Program Purpose:
Interactive transaction-based linked list data structure using C++ object.
A transaction will be entered at the command line after a short prompt and
output will be displayed on the console. Note: a batch of input transactions
in a plain text file can be processed using redirection.

A linked list of book IDs, titles, and quantities will be created and updated using
addBook, removeBook, orderBook, sellBook, and list transactions.
*/

#include <iostream>
#include <limits>
#include <sstream>
#include "book_f25.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

using namespace std;

// ORIGINAL MAIN - only compiled for terminal use (not web)
#ifndef __EMSCRIPTEN__
int main()
{
    book_f25 bookList;  // Create book_f25 object
    string transaction; // string variable for user input
    while (true)
    {
        // get transactions input from user
        std::cout << "enter transaction: ";
        std::getline(cin, transaction); // get entire line of user input

        if (transaction.empty())
            continue; // skip empty lines

        // Adds blank new line for cleaner output formatting
        std::cout << std::endl;

        // Get specific transaction (A, R, O, S, L, Q)
        char command = transaction[0]; // extracts first character as the "command"

        switch (command)
        {
        // Add book
        case 'A':
        {
            // Find first space (after 'A')
            size_t pos1 = transaction.find(' '); // size_t = unsigned integer type (only holds positive #s and 0)
            // Find second space (after ID)
            size_t pos2 = transaction.find(' ', pos1 + 1);

            // Extract ID substring (between spaces)
            string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);

            // converts to int
            int bookID = stoi(idStr);

            // Extract title (everything after second space)
            string title = transaction.substr(pos2 + 1);

            if (bookList.addBook(bookID, title)) // calls addBook method
                std::cout << "book added" << std::endl;
            else
                std::cout << "book not added" << std::endl;
            break;
        }

        // Remove book
        case 'R':
        {
            // Find space after 'R'
            size_t pos = transaction.find(' ');

            // Extract ID and convert to int
            string idStr = transaction.substr(pos + 1);
            int bookID = stoi(idStr);

            if (bookList.removeBook(bookID)) // calls removeBook method
                std::cout << "book removed" << std::endl;
            else
                std::cout << "book not removed" << std::endl;
            break;
        }

        // Order books
        case 'O':
        {
            // Find first space (after 'O')
            size_t pos1 = transaction.find(' ');
            // Find second space (after ID)
            size_t pos2 = transaction.find(' ', pos1 + 1);

            // Extract ID and quantity
            string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);
            string qtyStr = transaction.substr(pos2 + 1);

            int bookID = stoi(idStr);
            int quantity = stoi(qtyStr);

            if (bookList.orderBooks(bookID, quantity)) // calls orderBooks method
                std::cout << "books ordered" << std::endl;
            else
                std::cout << "books not ordered" << std::endl;
            break;
        }

        // Sell books
        case 'S':
        {
            // Find first space (after 'S')
            size_t pos1 = transaction.find(' ');
            // Find second space (after ID)
            size_t pos2 = transaction.find(' ', pos1 + 1);

            // Extract ID and quantity
            string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);
            string qtyStr = transaction.substr(pos2 + 1);

            int bookID = stoi(idStr);
            int quantity = stoi(qtyStr);

            if (bookList.sellBooks(bookID, quantity)) // calls sellBooks method
                std::cout << "books sold" << std::endl;
            else
                std::cout << "books not sold" << std::endl;
            break;
        }

        // List books
        case 'L':
            bookList.list(); // calls the list method
            break;

        // Quit
        case 'Q': // terminates the program as shown in instructions
            return 0;

        default: // default case (any invalid commands)
            std::cout << "Invalid transaction" << std::endl;
            break;
        }
    }

    return 0;
}
#endif

#ifdef __EMSCRIPTEN__
// WEB-ONLY: Global book list maintained across function calls
book_f25 webBookList;

// WEB-ONLY: Function exposed to JavaScript (does not affect terminal version)
std::string processTransaction(std::string transaction)
{
    if (transaction.empty())
    {
        return ""; // Skip empty transactions
    }

    // Get specific transaction (A, R, O, S, L, Q)
    char command = transaction[0];

    switch (command)
    {
    // Add book
    case 'A':
    {
        // Find first space (after 'A')
        size_t pos1 = transaction.find(' ');
        if (pos1 == string::npos)
            return "Invalid transaction";

        // Find second space (after ID)
        size_t pos2 = transaction.find(' ', pos1 + 1);
        if (pos2 == string::npos)
            return "Invalid transaction";

        // Extract ID substring (between spaces)
        string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);

        // converts to int
        int bookID = stoi(idStr);

        // Extract title (everything after second space)
        string title = transaction.substr(pos2 + 1);

        if (webBookList.addBook(bookID, title))
            return "book added";
        else
            return "book not added";
    }

    // Remove book
    case 'R':
    {
        // Find space after 'R'
        size_t pos = transaction.find(' ');
        if (pos == string::npos)
            return "Invalid transaction";

        // Extract ID and convert to int
        string idStr = transaction.substr(pos + 1);
        int bookID = stoi(idStr);

        if (webBookList.removeBook(bookID))
            return "book removed";
        else
            return "book not removed";
    }

    // Order books
    case 'O':
    {
        // Find first space (after 'O')
        size_t pos1 = transaction.find(' ');
        if (pos1 == string::npos)
            return "Invalid transaction";

        // Find second space (after ID)
        size_t pos2 = transaction.find(' ', pos1 + 1);
        if (pos2 == string::npos)
            return "Invalid transaction";

        // Extract ID and quantity
        string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);
        string qtyStr = transaction.substr(pos2 + 1);

        int bookID = stoi(idStr);
        int quantity = stoi(qtyStr);

        if (webBookList.orderBooks(bookID, quantity))
            return "books ordered";
        else
            return "books not ordered";
    }

    // Sell books
    case 'S':
    {
        // Find first space (after 'S')
        size_t pos1 = transaction.find(' ');
        if (pos1 == string::npos)
            return "Invalid transaction";

        // Find second space (after ID)
        size_t pos2 = transaction.find(' ', pos1 + 1);
        if (pos2 == string::npos)
            return "Invalid transaction";

        // Extract ID and quantity
        string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);
        string qtyStr = transaction.substr(pos2 + 1);

        int bookID = stoi(idStr);
        int quantity = stoi(qtyStr);

        if (webBookList.sellBooks(bookID, quantity))
            return "books sold";
        else
            return "books not sold";
    }

    // List books - return special marker
    case 'L':
        return "__LIST_BOOKS__"; // Special marker that JavaScript will handle

    // Clear (reset) - useful for web version
    case 'C':
        webBookList = book_f25(); // Create new empty book list
        return "book list cleared";

    default:
        return "Invalid transaction";
    }
}

// WEB-ONLY: Function to get the book list as a string
std::string getBookList()
{
    // Redirect cout to stringstream
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    // Call list() which outputs to cout
    webBookList.list();

    // Restore cout
    std::cout.rdbuf(old);

    // Return captured output
    return buffer.str();
}

// Bind the functions to JavaScript
EMSCRIPTEN_BINDINGS(book_module)
{
    emscripten::function("processTransaction", &processTransaction);
    emscripten::function("getBookList", &getBookList);
}
#endif