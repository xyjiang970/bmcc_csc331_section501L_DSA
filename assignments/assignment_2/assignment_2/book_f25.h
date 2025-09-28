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
class book_f25{
  public:
    bool addBook(int bookID, string title);
    // insert book on the linked list checking for duplicate.
    void list();
    // display books on the linked list.
    book_f25();
    //Default constructor
    //Sets start and last pointers to null.
  private:
    struct bookType{
      int ID_bt;        // ID
      string title_bt;  // title
      int qoh_bt;       // qty on hand
      bookType *next_bt;
    };
    bookType *first;
};
bool book_f25::addBook(int ID, string title) {
  bookType *p = first, *prev_p = first;
  bool found = false;
  while (p != NULL && !found) {
    found = (ID == p->ID_bt);
    prev_p = p;
    p = p->next_bt;
  }
  if (found)
    return false;
  else{
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
void book_f25::list() {
  if(first == NULL)
    cout << "No books." << endl;
  else {
    bookType *current=first;
    int i=0;
    while(current != NULL){
      i++;
      cout << i << ". " << current->ID_bt << " " << current->title_bt << " " << current->qoh_bt << endl;
      current=current->next_bt;
    }
  }
}
book_f25::book_f25(){
  first=NULL;
}



