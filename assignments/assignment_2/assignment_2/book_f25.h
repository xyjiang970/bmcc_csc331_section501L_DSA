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
  bookType *first;
};

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

bool book_f25::removeBook(int ID)
{
  bookType *p = first, *prev_p = NULL;
  bool found = false;

  // Search for the book
  while (p != NULL && !found)
  {
    found = (ID == p->ID_bt);
    if (!found)
    {
      prev_p = p;
      p = p->next_bt;
    }
  }

  if (found)
  {
    // Remove the node
    if (prev_p == NULL)
    {
      // Removing first node
      first = p->next_bt;
    }
    else
    {
      // Removing middle or last node
      prev_p->next_bt = p->next_bt;
    }
    delete p;
    return true;
  }
  return false;
}

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
