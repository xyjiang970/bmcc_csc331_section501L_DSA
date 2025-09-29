/*
csc331-section_501L prog1 Xin Yu (Jason) Jiang
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
        // get transactions input from user
        std::cout << "enter transaction: ";
        std::getline(cin, transaction);

        if (transaction.empty())
            continue; // skip empty lines

        // Adds new line for cleaner output formatting
        std::cout << std::endl;

        // Get specific transaction (A, R, O, S, L, Q)
        char command = transaction[0];

        switch (command)
        {
        // Add book
        case 'A':
        {
            // Find first space (after 'A')
            size_t pos1 = transaction.find(' ');
            // Find second space (after ID)
            size_t pos2 = transaction.find(' ', pos1 + 1);

            // Extract ID substring and convert to int
            string idStr = transaction.substr(pos1 + 1, pos2 - pos1 - 1);
            int bookID = stoi(idStr);

            // Extract title (everything after second space)
            string title = transaction.substr(pos2 + 1);

            if (bookList.addBook(bookID, title))
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

            if (bookList.removeBook(bookID))
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

            if (bookList.orderBooks(bookID, quantity))
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

            if (bookList.sellBooks(bookID, quantity))
                std::cout << "books sold" << std::endl;
            else
                std::cout << "books not sold" << std::endl;
            break;
        }

        // List books
        case 'L':
            bookList.list();
            break;

        // Quit
        case 'Q':
            return 0;

        default:
            std::cout << "Invalid transaction" << std::endl;
            break;
        }
    }

    return 0;
}