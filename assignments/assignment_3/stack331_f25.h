// stack331_f25.h
// kbyron@bmcc.cuny.edu
// 9/16/25
// C++ class with stack operations
using namespace std;
class stack331_f25{
  public:
    bool empty();
    void pop();
    void push(double num);
    double top();
    stack331_f25();
  private:
    struct stackNode{
      double stackNum;
      stackNode *next;
    };
    stackNode *head,*temp;
};
bool stack331_f25::empty(){
  return(head == NULL);
}
void stack331_f25::pop(){
  if(empty())
    cout << "pop() function failed ... empty stack.\n";
  else{
    temp = head;
    head = head->next;
    delete temp;
  }
}
void stack331_f25::push(double num){
  temp = new stackNode{num,head};
  head = temp;
}
double stack331_f25::top(){
  if(head == NULL){
    cout << "top() function failed ... empty stack.\n";
    return -1;
  }
  else
    return head->stackNum;
}
stack331_f25::stack331_f25(){ //default constructor
  head = NULL;
}

