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
  // insert book on the linked list checking for duplicate.
  bool addBook(int bookID, string title);

  // display books on the linked list.
  void list();

  // adding remaining functions as per instructions
  bool removeBook(int bookID);
  bool orderBooks(int bookID, int quantity);
  bool sellBooks(int bookID, int quantity);

  // Default constructor
  // Sets start and last pointers to null.
  book_f25();

private:
  struct bookType
  {
    int ID_bt;       // ID
    string title_bt; // title
    int qoh_bt;      // qty on hand
    bookType *next_bt;
  };

  // head pointer of the linked list
  // pointer variable named first that points to a bookType structure (node in the linked list)
  bookType *first;
};

// Adds a book to the list, returns true if successful
bool book_f25::addBook(int ID, string title)
{
  // p is pointer for traversing the list
  // prev_p tracks previous node
  bookType *p = first, *prev_p = first;
  bool found = false;

  // Loop through the list until end or duplicate found
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt); // check if current node's ID matches new ID
    prev_p = p;               // save current node as previous
    p = p->next_bt;           // move to next node
  }
  if (found) // if duplicate is found, do not add book!
    return false;

  // creation of new book (new node)
  else
  {
    bookType *newBook = new bookType; // new book (new node)
    newBook->ID_bt = ID;
    newBook->title_bt = title;
    newBook->qoh_bt = 0;     // initializing the quantity, need to use Order function to increase qoh
    newBook->next_bt = NULL; // next pointer is set to NULL (last node)

    // if list is empty, make newBook the FIRST node
    if (prev_p == NULL)
      first = newBook;
    else
      prev_p->next_bt = newBook;
    return true;
  }
}

// Removes a book, returns true if successful
bool book_f25::removeBook(int ID)
{
  bookType *p = first, *prev_p = NULL;
  bool found = false;

  // Search for the book
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt);

    // only move pointers if not found (stops when found)
    if (!found)
    {
      prev_p = p;
      p = p->next_bt;
    }
  }

  if (found)
  {
    // Remove the node
    if (prev_p == NULL) // if found and first node, update first to skip it
    {
      // Removing first node
      first = p->next_bt;
    }
    else // otherwise, link previous node to next node (bypass current)
    {
      // Removing middle or last node
      prev_p->next_bt = p->next_bt;
    }
    delete p;    // free memory of removed node
    return true; // true if found
  }
  return false; // false if not found
}

// Increases inventory, book must first exist!
bool book_f25::orderBooks(int ID, int quantity)
{
  bookType *p = first;
  bool found = false;

  // Search for the book
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt);
    if (!found)
    {
      p = p->next_bt;
    }
  }

  if (found)
  {
    // Increase quantity
    p->qoh_bt += quantity;
    return true;
  }
  return false;
}

// Decreases inventory, book must first exist!
bool book_f25::sellBooks(int ID, int quantity)
{
  bookType *p = first;
  bool found = false;

  // Search for the book
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt);
    if (!found)
    {
      p = p->next_bt;
    }
  }

  if (found)
  {
    // Decrease quantity
    p->qoh_bt -= quantity;
    return true;
  }
  return false;
}

// Displays all books
void book_f25::list()
{
  if (first == NULL)
    std::cout << "No books." << endl;

  else
  {
    bookType *current = first; // starts at first node
    int num_books = 0;         // counter variable
    while (current != NULL)    // loops through each node
    {
      num_books++;

      // print: number, ID, title, quantity
      std::cout << num_books << ". " << current->ID_bt << " " << current->title_bt << " " << current->qoh_bt << endl;
      current = current->next_bt; // move to next node
    }
  }
}

// Constructor (initializes the list)
book_f25::book_f25()
{
  first = NULL; // empty list starts with first pointing to nothing
}
