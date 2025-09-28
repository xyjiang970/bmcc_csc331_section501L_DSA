//************************************************************
// Author: CSC331
// 8-28-2025
//
// class book_f25
// This class specifies the members to implement
// a linked list of books and quantities.
//************************************************************
#include <string>
using namespace std;

class book_f25
{
public:
  bool addBook(int bookID, string title);
  // insert book on the linked list checking for duplicate.
  void list();
  // display books on the linked list.
  book_f25();
  // Default constructor
  // Sets start and last pointers to null.
private:
  struct bookType
  {
    int ID_bt;       // ID
    string title_bt; // title
    int qoh_bt;      // qty on hand
    bookType *next_bt;
  };
  bookType *first;
};

/*
Add – To add a book to the linked list, process a transaction in the form of “A”,
space, ID, space, title. For example: “A 10 book1”.  If the new book ID is not on
the linked list, the book ID and title will be added to the end of the linked list
with quantity set to zero.  If the book ID is already on the list, the transaction will
fail. One of two messages will be displayed: (1) “book added” or (2) “book not
added”.
*/
bool book_f25::addBook(int ID, string title)
{
  bookType *p = first, *prev_p = first;
  bool found = false;
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt);
    prev_p = p;
    p = p->next_bt;
  }
  if (found)
    return false;
  else
  {
    bookType *newBook = new bookType;
    newBook->ID_bt = ID;
    newBook->title_bt = title;
    newBook->qoh_bt = 0;
    newBook->next_bt = NULL;
    if (prev_p == NULL)
      first = newBook;
    else
      prev_p->next_bt = newBook;
    return true;
  }
}

/*
Remove – To remove a book from the linked list, process a transaction in the
form of “R”, space, ID.  For example: “R 10”.  If the book ID is on the list, the
book will be removed from the linked list.  If the book ID is not on the list, the
transaction will fail. One of two messages will be displayed: (1) “book removed”
or (2) “book not removed”.
*/

/*
Order – To order a quantity of books, process a transaction in the form of “O”,
space, ID, space, quantity. For example: “O 10 7”.  If the book ID is not on the
linked list, the transaction will fail.  If the book ID is on the list, the quantity for
the book will be increased by the quantity amount on the transaction. One of
two messages will be displayed: (1) “order added” or (2) “order not added”.
*/

/*
Sell – To sell a quantity of books, process a transaction in the form of “S”, space,
ID, space, quantity. For example: “S 10 7”.  If the book ID is not on the linked list,
the transaction will fail.  If the book ID is on the list, the quantity amount for the
book will be decreased by the quantity amount on the transaction. One of two
messages will be displayed: (1) “books sold” or (2) “books not sold”.
*/

/*
List – To display the books in a numbered list, enter a transaction in the form of
“L”.  Each book (ID, title and quantity) in the linked list will be displayed next to a
sequential number. Each book will be on a line by itself.
*/
void book_f25::list()
{
  if (first == NULL)
    cout << "No books." << endl;
  else
  {
    bookType *current = first;
    int i = 0;
    while (current != NULL)
    {
      i++;
      cout << i << ". " << current->ID_bt << " " << current->title_bt << " " << current->qoh_bt << endl;
      current = current->next_bt;
    }
  }
}

book_f25::book_f25()
{
  first = NULL;
}

/*
Quit – To terminate the program, enter a transaction in the form of “Q”.
*/